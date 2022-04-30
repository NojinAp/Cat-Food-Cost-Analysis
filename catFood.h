/*
    ==================================================
    Cat Food Cost Analysis
    ==================================================
*/

#define NUM_GRAMS 64
#define MAX_PRODUCT 3
#define KG 2.20462

struct CatFoodInfo 
{
	int sku;
	double price;
	int calories;
	double weight;
};

struct ReportData 
{
	int sku;
	double price;
	double weight;
	double kg;
	int g;
	int calories;
	double totalserving;
	double cost_serving;
	double cost_calorie;
};

//Gets user input of int type and validate for a positive non-zero number
int getIntPositive(int* num);

//Gets user input of double type and validate for a positive non-zero number
double getDoublePositive(double* num);

//Opening Message
void openingMessage(const int num_product);

//Gets user input for the details of cat food product
struct CatFoodInfo getCatFoodInfo(const int sequence_num);

//Displays the formatted table header
void displayCatFoodHeader(void);

//Displays a formatted record of cat food data
void displayCatFoodData(const int sku, const double* price, const int calories, const double* weight);

//Converts lbs: kg
double convertLbsKg(const double* lbs, double* result);

//Converts lbs: g
int convertLbsG(const double* lbs, int* result);

//Converts lbs: kg / g
void convertLbs(const double* lbs, double* kgresult, int* gresult);

//Calculates: servings based on gPerServ
double calculateServings(const double g, const double totalgrams, double* num2);

//Calculates: cost per serving
double calculateCostPerServing(const double* price, const double* totalserving, double* num2);

//Calculates: cost per calorie
double calculateCostPerCal(const double* price, const int* calories, double* num2);

//Derives a reporting detail record based on the cat food product data
struct ReportData calculateReportData(const struct CatFoodInfo cats);

//Displays the formatted table header for the analysis results
void displayReportHeader();

//Displays the formatted data row in the analysis table
void displayReportData(const struct ReportData rep, const int cheapest);

//Displays the findings (cheapest)
void displayFinalAnalysis(const struct CatFoodInfo cats);

//Logic entry point
void start();
