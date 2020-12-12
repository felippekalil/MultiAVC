#include "MenuBase.h"

namespace MenuExtensoes
{
	PiscaCiclo::PiscaCiclo() = default;

	PiscaCiclo::PiscaCiclo(const uint16_t aceso, const uint16_t apagado, const uint16_t tCiclo)
	{
		nAceso = aceso / tCiclo;
		nApagado = apagado / tCiclo;
		if (nAceso < 1)
			nAceso = 1;
		if (nApagado < 1)
			nApagado = 1;
	}

	void PiscaCiclo::reseta() { interacao = 0; }

	void PiscaCiclo::redefine(const uint16_t aceso, const uint16_t apagado, const uint16_t tCiclo)
	{
		nAceso = aceso / tCiclo;
		nApagado = apagado / tCiclo;
		if (nAceso < 1)
			nAceso = 1;
		if (nApagado < 1)
			nApagado = 1;
	}

	void PiscaCiclo::reseta(const uint16_t aceso, const uint16_t apagado, const uint16_t tCiclo)
	{
		redefine(aceso, apagado, tCiclo);
		reseta();
	}

	bool PiscaCiclo::aceso()
	{
		interacao++;
		if (interacao < nAceso)
			return true;
		if (interacao < nAceso + nApagado)
			return false;
		interacao = 0;
		return true;
	}

}
