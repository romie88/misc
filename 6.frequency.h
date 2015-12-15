/**
 * July's Selected Microsoft Classic 100 Interview Questions No. 6
 * 
 * This is a Tencent interview question. I first saw this in July's blog.
 * 
 * Given 10 numbers in the first row, fill out another 10 numbers in the second
 * row where the numbers in the second row is the number of times their
 * corresponding ones in the first row appears in the second row.
 * 
 * An example:
 * [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ] //1st row
 * [ 6, 2, 1, 0, 0, 0, 1, 0, 0, 0 ] //2nd row
 */

#include <vector>
#include <algorithm>

/**
 * The following solution is from July.
 * I am not sure why the iteration converges.
 * 
 * My test indicates that this solution will not converge for
 * n = 1, 2, 3, 5, 6.
 * 
 * For n = 1, 2, 3 if we simulate the iteration on paper we can see that
 * the freqs vector will enter a re-occuring pattern and never exit it.
 */
class SolutionJuly
{
public:
    SolutionJuly( unsigned int n )
    : nums( n ), freqs( n ) {
        
        for ( unsigned int i = 0; i < n; ++i )
            nums[ i ] = i;
        
        solve();
    }
    
    const std::vector< int > & getResult() const {
        return freqs;
    }
    
private:

    void solve() {
        while ( ! try_next() );
    }
    
    /**
     * iterate to calc the freqs vector
     * 
     * @return true if the freqs vector is not updated in the current iteration;
     *         false otherwise.
     */
    bool try_next() {
        bool done = true;
        for ( std::vector< int >::size_type i = 0;
              i < freqs.size(); ++i ) {
            const int f = get_freq( nums[ i ] );
            if ( freqs[ i ] != f ) {
                freqs[ i ] = f;
                done = false;
            }
        }
        return done;
    }
    
    /**
     * @param i the target number to scan in the freqs vector.
     * @return the number of times i appears in the freqs vector.
     */
    int get_freq( int i ) {
        int count = 0;
        for ( const auto f : freqs )
            if ( f == i ) ++count;
        return count;
    }
    
    std::vector< int > nums;
    std::vector< int > freqs;
};

/**
 * The following solution is by brute force.
 * It can handle all the possible inputs (negative and duplicates, etc.)
 * and it is general.
 * 
 * Denote a[] to be the first row.
 * Denote b[] to be the second row which is the frequency vector.
 * 
 * We can list a few observations:
 * 1. b[ 0] + ... + b[ n - 1 ] <= n
 * 2. a[ 0 ] * b[ 0 ] + ... + a[ n - 1 ] * b[ n - 1 ] <= n
 * 3. 0 <= b[ i ] <= n where i = 0, 1, ..., n - 1
 * 
 * With these we can prune some cases while we are enumerate all the potential
 * frequency vectors.
 * 
 * O( n^n * n^2 ) runtime
 * Actually this bound can be more tight by the number of ways to put
 * n balls into n slots timed by n^2.
 */
class SolutionBF
{
public:
    SolutionBF( const std::vector< int > & input_nums )
    : nums( input_nums ), freqs( nums.size() ) {
        solve();
    }
    
    const std::vector< int > & getResult() const {
        return freqs;
    }
    
private:
    void solve() {
        if ( ! solve_bf( 0, nums.size() ) )
            std::cerr << "No solution!!!" << std::endl;
    }
    
    /**
     * @param i the current index to the freqs vector
     * @param k the nums left unallocated
     */
    bool solve_bf( const std::vector< int >::size_type   i,
                   const unsigned int                    k ) {
        if ( i == nums.size() ) {
            return verify_freqs();
        }
        
        if ( nums[ i ] < 0
          || static_cast< unsigned int >( nums[ i ] ) >= nums.size() ) {
            freqs[ i ] = 0;
            return solve_bf( i + 1, k );
        }
        
        unsigned int upper_bound
        = nums[ i ] == 0 ? nums.size() : nums.size() / nums[ i ];
        upper_bound = std::min( k, upper_bound );
        for ( unsigned int j = 0; j <= upper_bound; ++j ) {
            freqs[ i ] = j;
            if ( solve_bf( i + 1, k - j ) )
                return true;
        }
        return false;
    }
    
    bool verify_freqs() {
        for ( std::vector< int >::size_type i = 0;
              i < nums.size(); ++i ) {
            int count = 0;
            for ( const auto f : freqs )
                if ( f == nums[ i ] )
                    ++count;
            if ( count != freqs[ i ] )
                return false;
        }
        return true;
    }
    std::vector< int > nums;
    std::vector< int > freqs;
};

/**
 * There is some analytical solution for this problem without programming.
 * 
 * Denote a[] to be the first row.
 * Denote b[] to be the second row which is the frequency vector.
 * 
 * 1. b[ 0 ] + ... + b[ n - 1 ] <= n
 * 2. a[ 0 ] * b[ 0 ] + ... + a[ n - 1 ] * b[ n - 1 ] <= n
 * 3. 0 <= b[ i ] <= n where i = 0, 1, 2, ..., n - 1
 * 4. For any b[ j ] there exists i such that a[ i ] = b[ j ] ??? not sure if this is true
 * 5. if a[ i ] < 0 or a[ i ] > n, then b[ i ] = 0
 * 6. There are at least two numbers from a[] such that their frequencies in b[]
 *    are not zeroes. ??? not sure if this is true
 * 
 * some more observations:
 * a. let b[ i ] be the minimum among all b[] elements. From 1. we know that
 *    n * b[ i ] <= n. Thus b[ i ] must be zero or one.
 *    If b[ i ] = 1 then all b[] are ones. The only case for this to hold is
 *    that a[] = { 1 } which is a trivial case we won't consider from now on.
 *    So one of the b[] must be zero.
 * b. Because there exists one zero in b[]. The frequency of zero is > 0.
 *    Without loss of generality let a[ 0 ] = 0 then b[ 0 ] > 0.
 *    b[ 0 ] < n and there is at least one non-zero b[ 1, ..., n - 1 ]. ???
 *    The totally non-zero frequencies is n - b[ 0 ]. ???
 * c. From 2 a[ i ] * b[ i ] <= n, i.e., b[ i ] <= n / a[ i ].
 *    If b[ i ] <= n / a[ i ] < 2 then a[ i ] > n / 2 must have b[ i ] < 2.
 *    Let's check some examples.
 *    If n = 10, then a[ i ] > 5 must have b[ i ] < 2.
 *    a[ 6 ] = 6, a[ 7 ] = 7, a[ 8 ] = 8, a[ 9 ] = 9
 *    If b[ 6 ] = b[ 7 ] = b[ 8 ] = b[ 9 ] = 0 then b[ 0 ] >= 4 and b[ 4 ] >= 1.
 *    If b[ 4 ] > 1, let's say b[ 4 ] = 2 then b[ 2 ] = 1 and thus b[ 1 ] = 1.
 *    Then b[ 1 ] actually should be 2. And b[ 2 ] = 1.
 *    ...
 *    If n = 9, then a[ i ] > 4 must have b[ i ] < 2.
 *    a[ 5 ] = 5, a[ 6 ] = 6, a[ 7 ] = 7, a[ 8 ] = 8
 *    If b[ 5 ] = b[ 6 ] = b[ 7 ] = b[ 8 ] = 0 then b[ 0 ] >= 4 and b[ 4 ] >= 1.
 *    If b[ 4 ] > 1, let's say b[ 4 ] = 2 then b[ 2 ] = 1 and thus b[ 1 ] = 1.
 *    Then b[ 1 ] actually should be 2. And b[ 2 ] = 1.
 *    ...
 *    ??? not sure how to proceed
 * 
 * If a[] has no 0 then b[] has to be all zeroes.
 * If a[] has no 0, 1, 2, n - 4 then b[] has no solution.
 * otherwise 0 has frequency n - 4, 1 has frequency 2, 2 has frequency 1,
 * n - 4 has frequency 1, the rest are zeroes.
 */
 
