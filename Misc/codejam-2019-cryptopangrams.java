import java.math.BigInteger;
import java.util.*;
import java.io.*;

public class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        
        int T = in.nextInt(); 
	    for(int i=1 ; i<=T ; ++i) {
	        String Ns = in.next();
	        int L = in.nextInt();
	        
	        BigInteger[] products = new BigInteger[L];
	        BigInteger[] code = new BigInteger[L+1];
	        TreeSet<BigInteger> nums = new TreeSet<BigInteger>();
	        
	        for(int j=0 ; j<L ; ++j) {
	            products[j] = new BigInteger(in.next());
	        }
	        
	        for(int j=0 ; j<L ; ++j) {
	            if(j>0) {
	            	if(!products[j].equals(products[j-1])) {
	            		BigInteger gcd = products[j].gcd(products[j-1]);
		                code[j] = gcd;
		                nums.add(code[j]);
		                int p = j-1, n = j+1;
		                
		                //move back to fix equals
		                BigInteger last = gcd;
		                while(p > 0 && products[p].equals(products[p-1])) {
		                	code[p] = products[p].divide(last);
		                	last = code[p];
		                	nums.add(code[p]);
		                	//System.out.println("At " + p + ", code = " + code[p] + ", last gcd was = " + last);
		                	if(p == 1) {
		                		code[0] = products[0].divide(last);
		                    	nums.add(code[0]);
		                	}
		                	--p;
		                }
		                // Handle first
		                if(j == 1) {
		                    code[0] = products[0].divide(last);
		                    nums.add(code[0]);
		                }
		                
		                //move forward to fix equals
						last = gcd;
						while(n < L && products[n].equals(products[n-1])) {
							code[n] = products[n-1].divide(last);
							last = code[n];
							nums.add(code[n]);
							if(n == L-1) {
								code[L] = products[L-1].divide(last);
		                    	nums.add(code[L]);	
							}
							++n;
						}
						// Handle last
						if(j == L-1) {
		                    code[L] = products[L-1].divide(last);
		                    nums.add(code[L]);
		                }
	            	}
	            }
	        }

            HashMap<BigInteger, String> map = new HashMap<BigInteger, String>();	        
	        String ch = "A";
	        
	        for(BigInteger b: nums) {
	            map.put(b, ch);
	            
	            if(ch.charAt(0) != 'Z') {
	            	ch = Character.toString((char)(ch.charAt(0) + 1));
	            }
	            
	        }
	        
	        System.out.print("Case #" + i + ": ");
	        for(int j=0; j<code.length ; ++j) {
	            System.out.print(map.get(code[j]));
	        }
	        System.out.println();
	        System.out.flush();
	    }
	}
}

// Input
// 4
// 103 31
// 217 1891 4819 2291 2987 3811 1739 2491 4717 445 65 1079 8383 5353 901 187 649 1003 697 3239 7663 291 123 779 1007 3551 1943 2117 1679 989 3053
// 10000 25
// 3292937 175597 18779 50429 375469 1651121 2102 3722 2376497 611683 489059 2328901 3150061 829981 421301 76409 38477 291931 730241 959821 1664197 3057407 4267589 4729181 5335543
// 107 29
// 15 15 15 15 21 49 77 143 221 323 437 667 899 1147 1517 1763 2021 2491 3127 3599 4087 4757 5183 5767 6557 7387 8633 9797 10403
// 107 28
// 15 15 15 21 49 77 143 221 323 437 667 899 1147 1517 1763 2021 2491 3127 3599 4087 4757 5183 5767 6557 7387 8633 9797 10403
  
// Output
// Case #1: CJQUIZKNOWBEVYOFDPFLUXALGORITHMS
// Case #2: SUBDERMATOGLYPHICFJKNQVWXZ
// Case #3: ABABACCDEFGHIJKLMNOPQRSTUVWXYZ
// Case #4: BABACCDEFGHIJKLMNOPQRSTUVWXYZ
