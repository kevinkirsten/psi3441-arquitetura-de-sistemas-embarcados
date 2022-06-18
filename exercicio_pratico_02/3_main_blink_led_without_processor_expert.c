#define SIM_SCGC5   (*((volatile unsigned int*)0x40048038)) /* System Integration Module System Clock Gating Control Register 5 */
#define PORTB_PCR19 (*((volatile unsigned int*)0x4004A04C)) /* Port B Pin Control Register 19 */
#define GPIO_PDDR   (*((volatile unsigned int*)0x400FF054)) /* Port B Data Direction Register */
#define GPIO_PDOR   (*((volatile unsigned int*)0x400FF040)) /* Port B Data Output Register */
#define GPIOB_PTOR  (*((volatile unsigned int*)0x400FF04C)) /* Port B Toggle Output Register */

#define GREEN_PIN     (19)
#define GREEN_SHIFT   (1<<GREEN_PIN)
#define GREEN_TOGGLE  (GPIOB_PTOR |= GREEN_SHIFT)

void delayMs(int n) {
	int i, j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < 7000; j++) {}
}

int main(void) {
	/* Turn on clock to PortB module */
	SIM_SCGC5 |= 0x400;

	/* Set the PTB19 pin multiplexer to GPIO mode */
	PORTB_PCR19 |= 0x0100; /* Enable MUX as 001 (GPIO) | SRE as 0 (Fast) */

	/* Set the pins direction to output */
	GPIO_PDDR |= GREEN_SHIFT;
	
	/* Set the initial output state to high */
	GPIO_PDOR |= GREEN_SHIFT;

	while(1) {
		GREEN_TOGGLE; /* Toggles the LED On and Off */
		delayMs(200); /* Wait 200ms */
	}
	return 0;
}
