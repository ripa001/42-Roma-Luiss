import System.IO
import System.Environment
import Data.List
import Crypto.Hash.SHA512 (hash)
import System.Random (mkStdGen, randomRs)



main :: IO()
main = do
    (name:_) <- getArgs
    if existent name
        then alreadyExistent
        else save name
