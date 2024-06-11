const int HL=2;//hash layer
using ALH=array<LL,HL>;
namespace HC{//Hash Const
	const int TABLE_SIZE=500;
	const int table[TABLE_SIZE]={7,9,21,33,87,93,97,103,123,181,207,223,241,271,289,297,321,349,363,403,409,411,427,433,439,447,453,459,483,513,531,579,607,613,637,663,711,753,787,801,829,861,871,891,901,919,931,933,993,1011,1021,1053,1087,1099,1137,1161,1203,1213,1237,1263,1269,1273,1279,1311,1329,1333,1351,1371,1393,1413,1447,1449,1491,1501,1531,1537,1539,1581,1617,1621,1633,1647,1663,1677,1699,1759,1773,1789,1791,1801,1803,1819,1857,1887,1917,1927,1957,1963,1969,2043,2089,2103,2139,2149,2161,2173,2187,2193,2233,2239,2277,2307,2359,2361,2431,2449,2457,2499,2571,2581,2607,2631,2637,2649,2667,2727,2791,2803,2821,2823,2827,2907,2937,2989,3009,3013,3051,3057,3097,3111,3133,3153,3157,3163,3211,3241,3247,3253,3267,3271,3273,3283,3309,3337,3351,3357,3373,3379,3397,3469,3471,3513,3519,3559,3577,3579,3601,3621,3643,3651,3663,3679,3709,3747,3751,3769,3777,3787,3793,3843,3853,3871,3889,3891,3909,3919,3931,3951,3957,3967,3987,3999,4023,4059,4099,4119,4123,4207,4233,4249,4251,4263,4321,4329,4381,4389,4437,4449,4459,4497,4507,4519,4539,4567,4569,4581,4609,4611,4627,4633,4647,4693,4699,4717,4771,4777,4783,4791,4807,4839,4843,4849,4857,4867,4869,4891,4893,4897,4927,4933,4977,4981,5001,5029,5053,5067,5103,5133,5187,5197,5203,5233,5277,5287,5299,5317,5329,5341,5353,5361,5403,5407,5437,5443,5449,5451,5469,5491,5527,5541,5547,5583,5631,5647,5683,5731,5737,5751,5763,5791,5823,5827,5833,5847,5863,5899,5907,5947,5953,5959,5971,5973,5991,5997,6019,6027,6037,6039,6061,6093,6099,6127,6129,6177,6193,6211,6223,6229,6307,6313,6331,6349,6379,6393,6417,6421,6457,6459,6477,6541,6571,6577,6583,6607,6621,6661,6663,6697,6717,6751,6781,6837,6867,6901,6957,6961,6967,6981,7003,7023,7027,7089,7117,7137,7147,7159,7191,7209,7237,7243,7257,7279,7321,7347,7383,7389,7417,7429,7447,7453,7467,7479,7497,7513,7521,7531,7537,7557,7633,7647,7651,7653,7681,7707,7719,7741,7759,7773,7803,7819,7837,7873,7887,7909,7923,7927,7929,7941,8041,8083,8089,8101,8109,8127,8173,8181,8223,8257,8259,8271,8277,8311,8313,8343,8349,8397,8403,8419,8431,8439,8487,8511,8557,8593,8617,8637,8649,8661,8671,8679,8719,8727,8761,8773,8791,8797,8803,8811,8829,8853,8899,8917,8937,8967,9009,9013,9063,9081,9093,9099,9123,9133,9163,9183,9211,9223,9259,9277,9279,9289,9301,9321,9331,9363,9399,9403,9421,9441,9457,9469,9487,9519,9529,9531,9541,9559,9561,9567,9573,9579,9597,9601,9609,9631,9651,9667,9679,9711,9733,9739,9757,9789,9831,9859,9867,9961,9999,10029,10051,10069,10101,10153,10173,10189,10197,10233,10243,10251,10267,10281};
	auto GP=[]()->int{return 1'000'000'000+table[rng()%TABLE_SIZE];};//generate modular
	const int MOD[4]={GP(),GP(),GP(),GP()};
	const int P[4]={13331,233,131,19260817};
	LL ksm[N][4];
	void init(){
		for(int j=0;j<HL;j++){
			ksm[0][j]=1;
			for(int i=1;i<N;i++){
				ksm[i][j]=(ksm[i-1][j]*P[j])%MOD[j];
			}
		}
	}
}
class Hash{
private:
	vector<ALH>h;
	bool sign;//0:normal 1:reverse
public:
	Hash(){}
	Hash(char *s,int n,bool sign_=0){
		init(s,n,sign_);
	}
	void init(char *s,int n,bool sign_=0){//s stores at pos [1,n], and just give para s (NOT s+1)
		h.resize(n+2);
		sign=sign_;
		if(!sign){
			for(int j=0;j<HL;j++){
				h[0][j]=0;
				for(int i=1;i<=n;i++){
					h[i][j]=(h[i-1][j]*HC::P[j]+s[i]-'a'+1)%HC::MOD[j];
				}
			}
		}
		else{
			for(int j=0;j<HL;j++){
				h[n+1][j]=0;
				for(int i=n;i>0;i--){
					h[i][j]=(h[i+1][j]*HC::P[j]+s[i]-'a'+1)%HC::MOD[j];
				}
			}
		}
	}
	ALH calc(const int& l,const int& r){
		static ALH ret;
		if(!sign){
			for(int j=0;j<HL;j++){
				ret[j]=h[r][j]-h[l-1][j]*HC::ksm[r-l+1][j];
			}
		}
		else{
			for(int j=0;j<HL;j++){
				ret[j]=h[l][j]-h[r+1][j]*HC::ksm[r-l+1][j];
			}
		}
		for(int j=0;j<HL;j++){
			ret[j]=(ret[j]%HC::MOD[j]+HC::MOD[j])%HC::MOD[j];
		}
		return ret;
	}
	static bool check(const ALH& a,const ALH& b){
		for(int i=0;i<HL;i++){
			if(a[i]!=b[i]) return 0;
		}
		return 1;
	}
};
ALH operator <<(const ALH& A,const int& len){
	static ALH ret;
	for(int i=0;i<HL;i++){
		ret[i]=(A[i]*HC::ksm[len][i])%HC::MOD[i];
	}
	return ret;
}
ALH operator +(const ALH& A,const ALH& B){
	static ALH ret;
	for(int i=0;i<HL;i++){
		ret[i]=(A[i]+B[i])%HC::MOD[i];
	}
	return ret;
}
ALH operator -(const ALH& A,const ALH& B){
	static ALH ret;
	for(int i=0;i<HL;i++){
		ret[i]=((A[i]-B[i])%HC::MOD[i]+HC::MOD[i])%HC::MOD[i];
	}
	return ret;
}
ALH operator *(const ALH& A,const ALH& B){
	static ALH ret;
	for(int i=0;i<HL;i++){
		ret[i]=A[i]*B[i]%HC::MOD[i];
	}
	return ret;
}