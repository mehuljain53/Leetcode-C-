class Solution {
public:
    int gcd(int a, int b)
    {
        if (a == 0)
            return b;
        return gcd(b%a, a);
    }
    int nthMagicalNumber(int N, int A, int B) {
     
        //cout<<A<<" "<<B<<endl;
        long lcm = A*B/gcd(A,B);
        long mod = 1000000007;
        int p = A;
        int q = B;
        //cout<<gcd(A,B)<<" "<<lcm<<endl;
        vector<int> arr;
        int pc=1;
        int qc=1;
        int cur=0;
        while(cur<lcm){
            if(p<q){
                arr.push_back(p);
                cur=p;
                    pc++;
                    p=A*pc;
                    
            }else if(q<p){
                arr.push_back(q);
                cur=q;
                qc++;
                q=B*qc;
                
            }else{
                arr.push_back(p);
                cur=p;
                pc++;
                p=A*pc;
                qc++;
                q=B*qc;
                
            }
            //cout<<cur<<" ";
        }
        //cout<<endl;
        int x = arr.size();
        //cout<<x<<endl;
        
        long ans = (((N)/x)*lcm)%mod;
        //cout<<ans<<endl;
        if(N%x!=0)
            ans += (arr[N%x-1])%mod;
        //cout<<ans<<endl;
        return ans%mod;
    }
};