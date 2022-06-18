int main(void)
{
	int first = 0, second = 1, next, c;

	for(c = 0 ; c < 10 ; c++)
	{
	  if ( c <= 1 )
	    next = c;
	  else
	  {
	    next = first + second;
	    first = second;
	    second = next;
	  }
	}
	
	return 0;
}
