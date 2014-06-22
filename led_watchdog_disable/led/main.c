int main()
{
	led_init();
	while(2){
		led_on();
		delay(1);
		led_off();	
		delay(1);	
	}
}
