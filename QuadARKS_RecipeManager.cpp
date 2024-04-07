#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits> 

using namespace std;
const int days = 7;
const int meals = 3;
string daysOfWeek[days] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
struct Recipe
{
    vector<string> recipe;
    int m = 0;
};

Recipe add_line_in_vector(const string &line)
{
    Recipe recipe;
    stringstream get(line);
    string temp;
    while (getline(get, temp, ','))
    {
        if (temp != "directions")
        {
            recipe.m++; // Count the number of ingredients
        }
        else
        {
            // Stop parsing ingredients when "directions" is encountered
        }
        recipe.recipe.push_back(temp);
    }
    return recipe;
}

void searchRecipe(const string &file_name, const string &recipe_name)
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        cout << "ERROR: File is not open!" << endl;
        return;
    }
    string line;
    Recipe recipe;
    int flag = 0;
    while (getline(file, line))
    {
        recipe = add_line_in_vector(line);
        if (recipe_name == recipe.recipe[0])
        {
            flag = 1; // Recipe found
            cout << "Recipe Name: " << recipe.recipe[0] << endl;
            cout << "Category: " << recipe.recipe[1] << endl;
            cout << "Ingredients:" << endl;
            for (int i = 2; i < recipe.recipe.size(); ++i)
            {
                if (recipe.recipe[i] == "directions")
                {
                    cout << "Directions :" << endl;
                }
                else if (recipe.recipe[i] == "Directions :")
                {
                    continue;
                }
                else
                    cout << "-"<<recipe.recipe[i] << endl;
            }

            break; // No need to continue searching after finding the recipe
        }
    }
    if (flag == 0)
    {
        cout << "Recipe not found." << endl;
    }
    file.close();
}
void display_recipe_category(const string &file_name) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "ERROR: File is not open!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Recipe recipe = add_line_in_vector(line);
        cout << "Recipe: " << recipe.recipe[0] << " - Category: " << recipe.recipe[1] << endl;
    }
    
    file.close();
}
void displayMP()
{
    std::ifstream file("Book.csv");
    if (!file.is_open())
    {
        std::cout << "ERROR: Unable to open file!" << std::endl;
        return;
    }

    std::string line;
    getline(file, line); // Read and discard the header line

    std::cout << "Meal Planner" << std::endl;
    for (int i = 0; i < days; ++i)
    {
        std::cout << "Day " << i + 1 << " (" << daysOfWeek[i] << "):" << std::endl;
        for (int j = 0; j < meals; ++j)
        {
            std::string meal;
            if (getline(file, meal))
            {
                // Adjusting for the format of the CSV file
                std::string mealType;
                if (j == 0)
                    mealType = "Breakfast";
                else if (j == 1)
                    mealType = "Lunch";
                else
                    mealType = "Dinner";

                // Assuming the content of the CSV file matches the meal plan format
                std::cout << "Enter " << mealType << " for " << daysOfWeek[i] << ": " << meal << std::endl;
            }
            else
            {
                std::cout << "Error reading meal from file." << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    }
    file.close();
}

void saveToCSV(string mealPlan[days][meals]) {
    ofstream file("Book.csv");
    if (file.is_open()) {
        file << "Day,Meal\n";

        for (int i = 0; i < days; ++i) {
            for (int j = 0; j < meals; ++j) {
                string mealType;
                if (j == 0)
                    mealType = "Breakfast";
                else if (j == 1)
                    mealType = "Lunch";
                else
                    mealType = "Dinner";

                file << mealPlan[i][j] << "\n";
            }
        }

        file.close();
        cout << "Meal plan saved" << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}
int main()
{
    string file_name = "recipe_manager.csv";
    string recipe_name;
    string ingredient_name;
    string category_name;
    string recipeNameToDelete;
    string ingredient_name1;
    string ingredient_name2;
    string mealPlan[days][meals];
    int coveredDays[days] = {0};
    int daysCovered = 0;
    int choice;
    do
    {
        cout << "1. Search recipe" << endl;
        cout << "2. Search ingredient" << endl;
        cout << "3. Search by category" << endl;
        cout << "4. Add recipe" << endl;
        cout << "5. Delete recipe" << endl;
        cout << "6. Add or Replace Meal Planner" << endl;
        cout << "7. Display Meal Planner"<<endl;
        cout << "8. Show all recipe and category"<<endl;
        cout << "9. Exit"<<endl;
        cout << "Enter your choice: ";
              if (!(cin >> choice)) {
            // Input extraction failed, meaning it's not an integer
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear(); // clear the error state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore invalid input
            continue; // Repeat the loop to get a valid input
        }
        cin.ignore();  // consume newline
        switch (choice)
        {
        case 1:
            cout << "Enter recipe name to search: ";
            getline(cin, recipe_name);
            searchRecipe(file_name, recipe_name);
            break;
        case 2:
            cout << "Enter ingredient name to search: ";
            getline(cin, ingredient_name);
            ingridientsearch(file_name, ingredient_name);
            break;
        case 3:
            cout << "Enter category type to search: ";
            getline(cin, category_name);
            categorysearch(file_name, category_name);
            break;
        case 4:
        {
            string rec_add_name, rec_add_type, rec_add_ing, rec_add_steps;
            cout << "Enter the recipe you want to add (name, type, ingredients, steps):" << endl;
            cout << "Enter the recipe name: ";
            getline(cin, rec_add_name);
            cout << "Enter the recipe type: ";
            getline(cin, rec_add_type);
            cout << "Enter the recipe ingredients: ";
            getline(cin, rec_add_ing);
            cout << "Enter the recipe steps: ";
            getline(cin, rec_add_steps);
            ofstream tempFile("recipe_manager.csv", ios::app);
            recipe_adder(rec_add_name, rec_add_type, rec_add_ing, rec_add_steps, tempFile);
            tempFile.close();
        }
        break;
        case 5:
        {
            string recipeNameToDelete;
            cout << "Enter the recipe name to delete: ";
            getline(cin, recipeNameToDelete);
            delete_recipe(file_name, recipeNameToDelete);
        }
        break;
        case 6:
            while (daysCovered < days){
                    int dayIndex;
        bool alreadyCovered = false;
        
        do {
            cout << "Enter the number of the day: " << endl;
            cout << "0 - Monday" << endl;
            cout << "1 - Tuesday" << endl;
            cout << "2 - Wednesday" << endl;
            cout << "3 - Thursday" << endl;
            cout << "4 - Friday" << endl;
            cout << "5 - Saturday" << endl;
            cout << "6 - Sunday" << endl;
            cin >> dayIndex;

            alreadyCovered = (coveredDays[dayIndex] == 1);
            if (alreadyCovered)
                cout << "Meal already planned for this day" << endl;

        } while (alreadyCovered || dayIndex < 0 || dayIndex >= days);

        cout << "Enter meals for " << daysOfWeek[dayIndex] << endl;
        cin.ignore(); // Ignore the newline character after entering the day index
        for (int j = 0; j < meals; ++j) {
            string mealType;
            if (j == 0)
                mealType = "breakfast";
            else if (j == 1)
                mealType = "lunch";
            else
                mealType = "dinner";

            cout << "Enter " << mealType << ": ";
            getline(cin, mealPlan[dayIndex][j]);
        }

        coveredDays[dayIndex] = 1;
        ++daysCovered;
        cout << endl;

        
        char editChoice;
        cout << "Do you want to edit the meals for this day? (y/n): ";
        cin >> editChoice;

        if (editChoice == 'y' || editChoice == 'Y') {
            cout << "Enter the index of the meal you want to edit (0 for breakfast, 1 for lunch, 2 for dinner): ";
            int mealIndex;
            cin >> mealIndex;

            if (mealIndex >= 0 && mealIndex < meals) {
                string newMeal;
                cout << "Enter the new meal: ";
                cin.ignore(); // Ignore the newline character after entering the meal index
                getline(cin, mealPlan[dayIndex][mealIndex]);
            } else {
                cout << "Invalid meal index." << endl;
            }
        }
    }
            saveToCSV(mealPlan);
            cout<<"Meal is Planned"<<endl;
            break;
        case 7:
            displayMP();
            break;
        case 8:
        display_recipe_category(file_name);
        break;
        default:
            if(choice!=9){
            cout << "Invalid choice. Please try again." << endl;
            }
        }
    } while (choice != 9 );
    return 0;
}
