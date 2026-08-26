/*******************************************************************
 * @file test_main.c
 *
 * @brief Testes unitários (ztest) da Atividade-01.
 *******************************************************************/

#include <zephyr/ztest.h>

ZTEST_SUITE(atividade01, NULL, NULL, NULL, NULL, NULL);

ZTEST(atividade01, test_placeholder)
{
	/* Atividade-01 não tem lógica isolada em função própria (só main()),
	 * então não há o que testar unitariamente ainda. Esse teste serve de
	 * esqueleto pra atividades futuras que exijam funções testáveis.
	 */
	zassert_true(true, "placeholder");
}
