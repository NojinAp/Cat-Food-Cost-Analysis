/*
	==================================================
	Cat Food Cost Analysis
	==================================================
	Name   : Nozhin Azarpanah
	Date   : October 18, 2021
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "catFood.h"

int getIntPositive(int* num) 
{
	int val;

	do
	{
		scanf("%d", &val);

		if (val <= 0) 
		{
			printf("ERROR: Enter a positive value: ");
		}

	} while (val <= 0);

	if (num != NULL) 
	{
		*num = val;
	}
	return val;
}

double getDoublePositive(double* num) 
{
	double val;
	do
	{
		scanf("%lf", &val);

		if (val <= 0) 
		{
			printf("ERROR: Enter a positive value: ");
		}

	} while (val <= 0);

	if (num != NULL) 
	{
		*num = val;
	}
	return val;
}

void openingMessage(const int num_product) 
{
	printf("Cat Food Cost Analysis");
	printf("\n======================");
	printf("\n\nEnter the details for %d dry food bags of product data for analysis.", num_product);
	printf("\nNOTE: A 'serving' is %dg\n", NUM_GRAMS);
}

struct CatFoodInfo getCatFoodInfo(const int sequence_num) 
{
	struct CatFoodInfo food = { 0 };

	printf("\nCat Food Product #%d\n", sequence_num);
	printf("--------------------\n");
	printf("SKU           : ");
	getIntPositive(&food.sku);
	printf("PRICE         : $");
	getDoublePositive(&food.price);
	printf("WEIGHT (LBS)  : ");
	getDoublePositive(&food.weight);
	printf("CALORIES/SERV.: ");
	getIntPositive(&food.calories);

	return food;
}

void displayCatFoodHeader(void)
{
	printf("SKU         $Price    Bag-lbs Cal/Serv\n");
	printf("------- ---------- ---------- --------\n");
}

void displayCatFoodData(const int sku, const double* price, const int calories, const double* weight) 
{
	printf("%07d %10.2lf %10.1lf %8d\n", sku, *price, *weight, calories);
}

double convertLbsKg(const double* lbs, double* result) 
{
	double kg;
	kg = *lbs / KG;

	if (result != NULL) 
	{
		*result = kg;
	}
	return kg;
}

int convertLbsG(const double* lbs, int* result) 
{
	int g;
	g = (*lbs / KG) * 1000;
	if (result != NULL) 
	{
		*result = g;
	}
	return g;
}

void convertLbs(const double* lbs, double* kgresult, int* gresult)
{
	double kg;
	kg = *lbs / KG;

	if (kgresult != NULL) 
	{
		*kgresult = kg;
	}

	int g;
	g = (*lbs / KG) * 1000;

	if (gresult != NULL) 
	{
		*gresult = g;
	}
}

double calculateServings(const double g, const double totalgrams, double* num2) 
{
	double totalserving;
	totalserving = totalgrams / g;

	if (num2 != NULL) 
	{
		*num2 = totalserving;
	}
	return totalserving;
}

double calculateCostPerServing(const double* price, const double* totalserving, double* num2)
{
	double cost_serving;
	cost_serving = *price / *totalserving;

	if (num2 != NULL)
	{
		*num2 = cost_serving;
	}
	return cost_serving;
}

double calculateCostPerCal(const double* price, const int* calories, double* num2) {
	double cost_calorie = *price / *calories;
	if (num2 != NULL)
		*num2 = cost_calorie;
	return cost_calorie;
}

struct ReportData calculateReportData(const struct CatFoodInfo cats) 
{
	struct ReportData report = { 0 };

	report.sku = cats.sku;
	report.price = cats.price;
	report.calories = cats.calories;
	report.weight = cats.weight;
	report.kg = convertLbsKg(&cats.weight, &report.kg);
	report.g = convertLbsG(&cats.weight, &report.g);
	report.totalserving = calculateServings(NUM_GRAMS, report.g, &report.totalserving);
	report.cost_serving = calculateCostPerServing(&cats.price, &report.totalserving, &report.cost_serving);
	calculateCostPerCal(&cats.price, &cats.calories, &report.cost_calorie);
	report.cost_calorie /= report.totalserving;

	return report;
}

void displayReportHeader()
{
	printf("\nAnalysis Report (Note: Serving = %dg\n", NUM_GRAMS);
	printf("---------------\n");
	printf("SKU         $Price    Bag-lbs     Bag-kg     Bag-g Cal/Serv Servings  $/Serv   $/Cal\n");
	printf("------- ---------- ---------- ---------- --------- -------- -------- ------- -------\n");
}

void displayReportData(const struct ReportData rep, const int cheapest) 
{
	if (cheapest != 0) 
	{
		printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf ***\n", rep.sku, rep.price, rep.weight, rep.kg, rep.g, rep.calories, rep.totalserving, rep.cost_serving, rep.cost_calorie);
	}
	else 
	{
		printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf\n", rep.sku, rep.price, rep.weight, rep.kg, rep.g, rep.calories, rep.totalserving, rep.cost_serving, rep.cost_calorie);
	}
}

void displayFinalAnalysis(const struct CatFoodInfo cats) 
{
	printf("\n");
	printf("Final Analysis\n");
	printf("--------------\n");
	printf("Based on the comparison data, the PURRR-fect economical option is:\n");
	printf("SKU:%07d Price: $%.2lf\n\nHappy shopping!\n", cats.sku, cats.price);
}

void start() 
{
	struct CatFoodInfo cats[MAX_PRODUCT] = { {0} };
	struct ReportData rep[MAX_PRODUCT] = { {0} };

	openingMessage(MAX_PRODUCT);
	int i;
	int index = 0;
	double cheapest = 1;

	for (i = 0; i < MAX_PRODUCT; i++)
	{
		cats[i] = getCatFoodInfo(i + 1);
	}

	printf("\n");
	displayCatFoodHeader();

	for (i = 0; i < MAX_PRODUCT; i++)
	{
		displayCatFoodData(cats[i].sku, &cats[i].price, cats[i].calories, &cats[i].weight);
	}

	displayReportHeader();

	for (i = 0; i < MAX_PRODUCT; i++)
	{
		rep[i] = calculateReportData(cats[i]);

		if (rep[i].cost_calorie < cheapest) 
		{
			cheapest = rep[i].cost_calorie;
			index = i;
		}

		rep[2].cost_calorie += 0.000005;
	}

	for (i = 0; i < MAX_PRODUCT; i++)
	{
		displayReportData(rep[i], i == index ? index + 1 : 0);
	}

	displayFinalAnalysis(cats[index]);
}