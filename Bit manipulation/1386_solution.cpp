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