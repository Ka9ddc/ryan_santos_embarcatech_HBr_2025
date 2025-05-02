#include "unity.h"
#include "hal_temp.h"

void setUp(void) {}
void tearDown(void) {}

void test_adc_to_celsius(void) { // Deve retornar 27 quando a tensão for 706 _should_return_27_when_voltage_is_0_706
    float tensao = 0.706f;
    float temperatura = adc_to_celsius(tensao);
    TEST_ASSERT_FLOAT_WITHIN(1.00f, 27.0f, temperatura); // Verifica se o valor da temperatura está no limite especificado
}

int main(void) { // Inicializa o unity e roda o teste.
    UNITY_BEGIN();
    RUN_TEST(test_adc_to_celsius);
    return UNITY_END();
}
