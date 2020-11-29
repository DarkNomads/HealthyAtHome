
-- cabal install random
-- cabal repl -b random # -b is short for --build-depends
-- stack ghci
import System.Random (randomRIO)
import Data.List
import System.IO

-- Constant
sleepH0 = 15
sleepH1 = 14
sleepH3_5 = 12
sleepH6_13 = 10
sleepH14_17 = 8
sleepHA = 8
sleepTip1 = "Stick to a sleep schedule.Set aside no more than eight hours for sleep. The recommended amount of sleep for a healthy adult is at least seven hours. Most people don't need more than eight hours in bed to achieve this goal."
sleepTip2 = "Pay attention to what you eat and drink. Don't go to bed hungry or stuffed. In particular, avoid heavy or large meals within a couple of hours of bedtime. Your discomfort might keep you up."
sleepTip3 = "Create a restful environment. Create a room that's ideal for sleeping. Often, this means cool, dark and quiet. Exposure to light might make it more challenging to fall asleep. Avoid prolonged use of light-emitting screens just before bedtime. Consider using room-darkening shades, earplugs, a fan or other devices to create an environment that suits your needs."
sleepTip4 = "Limit daytime naps Long. daytime naps can interfere with nighttime sleep. If you choose to nap, limit yourself to up to 30 minutes and avoid doing so late in the day."
sleepTip5 = "Include physical activity in your daily routine. Regular physical activity can promote better sleep. Avoid being active too close to bedtime, however."
sleepTip6 = "Manage worries. Try to resolve your worries or concerns before bedtime. Jot down what's on your mind and then set it aside for tomorrow."


-- Generate ramdom data to compare (unit: days)
sleepData :: Int -> IO([Int])
sleepData 0 = return []
sleepData n = do
  r  <- randomRIO (3,12)
  rs <- sleepData (n-1)
  return (r:rs) 

monthlyData = sleepData 30
weeklyData = sleepData 7



getReport :: Int -> Int -> String
getReport hours exHours = do
  let printV = exHours - hours
  if (hours < exHours)
    then ("You need to sleep " ++ (show printV) ++ " more hours")
    else "You had good sleep"

sleepCheck :: Int -> Int -> String
sleepCheck age hours =  case age of
  0 -> getReport hours sleepH0
  1 -> getReport hours sleepH1
  2 -> getReport hours sleepH1
  3 -> getReport hours sleepH3_5
  4 -> getReport hours sleepH3_5
  5 -> getReport hours sleepH3_5
  6 -> getReport hours sleepH6_13
  7 -> getReport hours sleepH6_13
  8 -> getReport hours sleepH6_13
  9 -> getReport hours sleepH6_13
  10 -> getReport hours sleepH6_13
  11 -> getReport hours sleepH6_13
  12 -> getReport hours sleepH6_13
  13 -> getReport hours sleepH6_13
  14 -> getReport hours sleepH14_17
  15 -> getReport hours sleepH14_17
  16 -> getReport hours sleepH14_17
  17 -> getReport hours sleepH14_17
  _ -> getReport hours sleepHA
 
toSleep :: Int -> String
toSleep x = do
  if(x > 19 && x <= 24)
    then "You had good sleep schedule"
    else "You need to sleep early"



main = do
  print "Function meun: "
  print " sleepData (int) -- Generate ramdom data to compare (unit: days)"
  print " sleepCheck (int1) (int2) -- Enter age(int1), hours(int2) slept yesterday"
  print " sleepTip(num) -- Print out sleep tips"


