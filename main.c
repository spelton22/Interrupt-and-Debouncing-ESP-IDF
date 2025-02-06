#include <esp_timer.h>
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define BUTTON 1
#define BUZZER 2
int x = 0;

void IRAM_ATTR gpio_isr(void * arg){
  if(gpio_get_level(BUTTON) == 0){
    gpio_set_level(BUZZER, 0);
  }else{
    gpio_set_level(BUZZER, 1);
  }
  x = 0;
}

void app_main() {
  gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << BUTTON),
    .mode = GPIO_MODE_INPUT, 
    .intr_type = GPIO_INTR_ANYEDGE, 
  };
  gpio_config(&io_conf);

  gpio_config_t io_conf2 = {
    .pin_bit_mask = (1ULL << BUZZER),
    .mode = GPIO_MODE_OUTPUT , 
  };
  gpio_config(&io_conf2);

  x = 0;

  gpio_install_isr_service(0);
  gpio_isr_handler_add(BUTTON, gpio_isr, (void *) BUTTON);

  // while(1){
  //   x++;
  //   gpio_set_level(BUZZER, 0);
  // }

}