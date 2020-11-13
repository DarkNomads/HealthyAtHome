% So far I just have the database created, still need to search for more recipes and do more data collection.
% Still working out the actual logic and how to input output with prolog. 

% foodGroup(Name, ListOfFoods).
foodGroup(fruits, [cranberry, apple, banana]). 
foodGroup(vegetables, [broccoli, zuchini]).
foodGroup(dairy, [milk, cheese, yogurt]).
foodGroup(meat, [beef, chicken, pork, lamb, eggs]).
foodGroup(nut, [almonds, peanuts, walnuts]).
foodGroup(confection, [sugar, mapleSyrup]).
foodGroup(grain, [wheat, rice, oats, cornmeal, barley]).
foodGroup(seeds, [chia, flax]).

% restriction(Name, foodGroupList, calLimit).
restriction(none, [], 0).
restriction(vegetarian, [meat], 0)
restriction(vegan, [meat, dairy], 0)
restriction(diabetic, [confection], 0)
restriction(diet, [], 400).

% meal(Category, mealName, Ingredients, PrepTime (mins), Calories (kCal), Protien (g), Carbs(g), Fat(g)).

% Yummylife Overnight Oats, 1 cup
meal(Breakfast, overnightOats, [oats, yogurt, milk, chia], 480, 264, 15, 55, 5).
% Love & Lemons granola
meal(Breakfast, homemadeGranola, [oats, mapleSyrup, cinnamon, almonds, walnuts, coconut, cranberry], 40, 174, 3, 20, 11).
% minimalistbaker dark chocolate quinoa breakfast bowl (vegan)
meal(Breakfast, darkChocolateQuinoaBreakfastBowl, [quinoa, almond, coconut, salt, cocoa, mapleSyrup, vanilla, darkChocolate], 30, 257, 12, 44, 6). 
%
meal(Breakfast,
%
meal(Breakfast,
%
meal(Breakfast,
%
meal(Breakfast,
%
meal(Breakfast,
%
meal(Breakfast,
%
meal(Breakfast,
%
meal(Lunch,
meal(Lunch,
meal(Lunch,
meal(Lunch,
meal(Lunch,
meal(Lunch,
meal(Lunch,
meal(Lunch,
meal(Lunch,
meal(Lunch,
meal(Dinner,
meal(Dinner,
meal(Dinner,
meal(Dinner,
meal(Dinner,
meal(Dinner,
meal(Dinner,
meal(Dinner,
meal(Dinner,
meal(Dinner,
meal(Snack,
meal(Snack,
meal(Snack,
meal(Snack,
meal(Snack,
meal(Snack,
meal(Snack,
meal(Snack,
meal(Snack,
meal(Snack,
