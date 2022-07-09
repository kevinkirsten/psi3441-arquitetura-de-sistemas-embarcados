#define SIM_SCGC5   (*((volatile unsigned int*)0x40048038)) /* System Integration Module System Clock Gating Control Register 5 */
#define SIM_SCGC6   (*((volatile unsigned int*)0x4004803C)) /* System Integration Module System Clock Gating Control Register 6 */

#define PORTE_PCR20 (*((volatile unsigned int*)0x4004D050)) /* Acquisition Port */
#define PORTB_PCR19 (*((volatile unsigned int*)0x4004A04C)) /* Port B Pin Control Register 19 (GREEN LED)*/
#define PORTB_PCR18 (*((volatile unsigned int*)0x4004A048)) /* Port B Pin Control Register 18 (RED LED) */
#define PORTD_PCR1  (*((volatile unsigned int*)0x4004C004)) /* Port D Pin Control Register 18 (BLUE LED) */

#define GPIOB_PDDR  (*((volatile unsigned int*)0x400FF054)) /* Port B Data Direction Register */
#define GPIOD_PDDR  (*((volatile unsigned int*)0x400FF0D4)) /* Port D Data Output Register */
#define GPIOE_PDDR  (*((volatile unsigned int*)0x400FF114)) /* Port E Data Output Register */

#define GPIOB_PDOR  (*((volatile unsigned int*)0x400FF040)) /* Port B Data Output Register */
#define GPIOD_PDOR  (*((volatile unsigned int*)0x400FF0C0)) /* Port D Data Output Register */

#define GPIOB_PTOR  (*((volatile unsigned int*)0x400FF04C)) /* Port B Toggle Output Register */
#define GPIOD_PTOR  (*((volatile unsigned int*)0x400FF0CC)) /* Port D Toggle Output Register */

#define GREEN_PIN     (19)
#define GREEN_SHIFT   (1<<GREEN_PIN)
#define GREEN_TOGGLE  (GPIOB_PTOR |= GREEN_SHIFT)

#define RED_PIN       (18)
#define RED_SHIFT     (1<<RED_PIN)
#define RED_TOGGLE    (GPIOB_PTOR |= RED_SHIFT)

#define BLUE_PIN       (1)
#define BLUE_SHIFT     (1<<BLUE_PIN)
#define BLUE_TOGGLE    (GPIOD_PTOR |= BLUE_SHIFT)

#define ADC0_SC1A (*((volatile unsigned int*)0x4003B000)) /* ADC Status and Control Registers 1 */
#define ADC0_CFG1 (*((volatile unsigned int*)0x4003B008)) /* ADC Configuration Register 1  */
#define ADC0_RA   (*((volatile unsigned int*)0x4003B010)) /* ADC Data Result Register */
#define ADC0_SC2  (*((volatile unsigned int*)0x4003B020)) /* Status and Control Register 2 */

void delayMs(int n) {
  int i, j;
  for(i = 0 ; i < n; i++)
    for (j = 0; j < 7000; j++) {}
}

int main(void) {
  /* Turn on clock to PortB module (GREEN/RED LED)*/
  SIM_SCGC5 |= 0x400;
  /* Turn on clock to PortD module (BLUE LED)*/
  SIM_SCGC5 |= 0x1000;
  /* Turn on clock to PortE module (Acquisition)*/
  SIM_SCGC5 |= 0x2000;
  /* Turn on clock to ADC0 module*/
  SIM_SCGC6 |= 0x8000000;

  /* Configure MUX to ADC acquisition */
  /* Configure DMA for ADC conversion */
  ADC0_SC2 &= ~(6<<1); 
  /* (input clock)/8 | Short sample time | 10-bit conversion | ALTCLK */
  ADC0_CFG1 &= ~0xF; 

  /* Pin is configured as general-purpose input */
  GPIOE_PDDR &= ~0x100000;

  /* Set the PTD1, PTB18 and PTB19 pin multiplexer to GPIO mode */
  PORTB_PCR19 |= 0x0100; // Enable MUX as 001 (GPIO) | SRE as 0 (Fast)
  PORTB_PCR18 |= 0x0100; // Enable MUX as 001 (GPIO) | SRE as 0 (Fast)
  PORTD_PCR1  |= 0x100;  // Enable MUX as 001 (GPIO) | SRE as 0 (Fast)
  PORTE_PCR20 &= ~0x700; // Enable MUX as 000 (analog)

  /* Set the pins direction to output */
  GPIOB_PDDR |= GREEN_SHIFT;
  GPIOB_PDDR |= RED_SHIFT;
  GPIOD_PDDR |= BLUE_SHIFT;

  /* Set the initial output state to high */
  GPIOB_PDOR |= GREEN_SHIFT;
  GPIOB_PDOR |= RED_SHIFT;
  GPIOD_PDOR |= BLUE_SHIFT;

  int adc_value;

  /* Loop with LED GREEN and RED blinking together */
  while(1) {
    /* ADTRG by software */
    ADC0_SC2 &= ~(6<<1);

    /* Start Conversion */
    /* Single-ended conversions and input channels are selected. */
    ADC0_SC1A &= ~0x7F;
    
    /* Wait for conversion to complete */
    while (ADC0_SC1A && 0x80) {};

    /* Read the ADC value */
    adc_value = ADC0_RA;

    /* Set the output state */
    if (adc_value > 200) {
      RED_TOGGLE;
      BLUE_TOGGLE;
    } else if (adc_value < 50) {
      BLUE_TOGGLE;
      RED_TOGGLE;
    } else {
      RED_TOGGLE;
      BLUE_TOGGLE;
    }
  }
  return 0;
}
