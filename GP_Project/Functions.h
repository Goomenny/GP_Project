#pragma once
float evaluate(int D, float tmp[], long *nfeval) {

	float result = 1;

	(*nfeval)++;

	for (int i = 0; i < D; i++)
	{
		result += tmp[i] * tmp[i];
	}


	return result-1.;
}