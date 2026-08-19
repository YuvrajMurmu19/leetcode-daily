/*
    Approach-1 (Bitmasking)

    Idea:
    - Represent the reserved seats of each row using an integer bitmask.
    - Bit 'seat' is set if that seat is reserved.

      Example:
          mp[row] |= (1 << seat);

    - Create masks representing the three possible group blocks:

          mask1 -> seats 2,3,4,5
          mask2 -> seats 4,5,6,7
          mask3 -> seats 6,7,8,9

    To check whether a group block is available:
          groupMask & reservedMask

    If the result is 0:
        -> None of the seats in that block are reserved.
        -> The block is available.

    For every affected row:

        If all three blocks are available:
            -> 2 groups

        Else if at least one block is available:
            -> 1 group

        Else:
            -> 0 groups

    Again, completely empty rows can accommodate 2 groups each:

        result = (n - number of affected rows) * 2

    Why bitmasking?
    - Seat availability can be represented using individual bits.
    - Checking multiple seats becomes a single bitwise AND operation.
    - This removes the need for unordered_set lookups.

    Time Complexity: O(m) average
        - Each reservation updates one bit.
        - Each affected row performs a constant number of bit operations.

    Space Complexity: O(m)
        - One integer mask is stored for each affected row.

    Key Takeaway:
    - This approach demonstrates how choosing a better data representation
      can make the solution much simpler and more efficient.
*/

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int,int> mp;

        int mask1 = (1<<2) | (1<<3) | (1<<4) | (1<<5);
        int mask2 = (1<<4) | (1<<5) | (1<<6) | (1<<7);
        int mask3 = (1<<6) | (1<<7) | (1<<8) | (1<<9);
        
        for(auto& bookedSeat:reservedSeats){
            int row = bookedSeat[0];
            int seat = bookedSeat[1];
            mp[row] = mp[row] | (1<<seat);
        }
        int result = (n-mp.size())*2;

        for(auto& [key,mask]:mp){

            int g1 = mask1 & mask;
            int g2 = mask2 & mask;
            int g3 = mask3 & mask;

            if(!g1 && !g2 && !g3){
                result+= 2;
            }else if(!g1 || !g2 || !g3) result+=1;
        }

        return result;

    }
};

/*
    Approach-2 (HashMap + HashSet)

    Idea:
    - Only rows containing reserved seats need to be processed.
    - Store the reserved seats of every affected row using:
          unordered_map<int, unordered_set<int>>
    - Every row without reservations can always accommodate 2 groups.

    For every affected row, check the three possible group blocks:
    - Seats 2,3,4,5
    - Seats 4,5,6,7
    - Seats 6,7,8,9

    If all three blocks are available:
        -> 2 groups can be seated.

    If at least one block is available:
        -> 1 group can be seated.

    Otherwise:
        -> 0 groups can be seated.

    Important:
    - The middle block (4,5,6,7) overlaps with both outer blocks.
    - Therefore, if all three blocks are available, only 2 groups
      can be formed, not 3.

    Initially:
        result = (n - number of affected rows) * 2

    This handles all completely empty rows directly.

    Time Complexity: O(m) average
        - Each reservation is inserted into a hash set once.
        - Each affected row checks only 12 seat positions.

    Space Complexity: O(m)
        - HashMap + HashSets store all reserved seats.
*/

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int,unordered_set<int>> mp;
        
        for(auto& bookedSeat:reservedSeats){
            int row = bookedSeat[0];
            int seat = bookedSeat[1];
            mp[row].insert(seat);
        }
        int result = (n-mp.size())*2;

        for(auto& [key,bookedSeats]:mp){
            auto isAvailable =[&](int seat){
               return bookedSeats.find(seat) == bookedSeats.end();
            };

            bool g1 = isAvailable(2) && isAvailable(3) && isAvailable(4) && isAvailable(5);
            bool g2 = isAvailable(4) && isAvailable(5) && isAvailable(6) && isAvailable(7);
            bool g3 = isAvailable(6) && isAvailable(7) && isAvailable(8) && isAvailable(9);

            if(g1 && g2 && g3){
                result+= 2;
            }else if(g1 || g2 || g3) result+=1;
        }

        return result;

    }
};