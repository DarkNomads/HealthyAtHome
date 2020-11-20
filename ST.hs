

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

sleepD = 1.5
sleepL = 6.5

-- RandomList generator
randomSleep :: Int -> IO([Int])
randomSleep 0 = return []
randomSleep n = do
  r  <- randomRIO (3,12)
  rs <- randomSleep (n-1)
  return (r:rs) 

randomDL :: Int -> IO([Int])
randomDL 0 = return []
randomDL n = do
  r  <- randomRIO (0,5)
  rs <- randomDL (n-1)
  return (r:rs) 

{- Sum a list
sumList :: IO([Int]) -> Int
sumList [] = 0
sumList (x:xs) = x + sumList xs
-}

sleepHours = randomSleep 30
deepSleepHours = randomDL 30
lightSleepHours = randomDL 30

averageHours = 9
averageDeep = 2
averageLight = 7



main = do
  print "30 Days Sleep Schedule (in hours): " 
  print "Average sleep hours in a month: " 
  print averageHours







