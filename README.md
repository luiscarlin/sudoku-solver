# sudoku solver

## Algorithm
Create a 2D 9x9 array
Fill out the array with the known values and write 0s for unknowns

// Start from top left corner (0, 0) to bottom right corner (8, 8)
If x >= 9 or y >= 9: then return true
Read the number in the current square
If value == 0 { 
    // this is an unknown
    assign possibleValue = 1
    while (1) {
        if (possibleValue > 9): return false

        test if possible value is a good candidate
        if it's a good candidate:
           if (move to next square and repeat == true): 
              return true

        possibleValue++
    }
}
else {
    // this is a known 
    return (move to the next square and repeat) 
}
