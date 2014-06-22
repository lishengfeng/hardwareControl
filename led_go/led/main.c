int main()
{
	int i = 100;
	led_init();
	while(i--){
		led_on();
		delay(100);
		led_off();	
		delay(100);	
	}
}
