int main()
{
	int i;
	clock_init();
	led_init();
	while(1){
		for(i=0;i<4;i++){
			led_on(i);
			delay(5);
			led_off(i);	
			delay(5);	
		}
	}
}
