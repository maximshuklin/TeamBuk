#define ts to_string
#define sts string ts
sts(const string &s) {return s;}
sts(bool b) {return (b ? "true" : "false");}
sts(char c) {return string(1, c);}
template<class A, class B>
sts(pair<A, B>);
template<class T>
sts(T v) {
    string s = "{", sep="";
    for (auto x : v) {
        s += sep;
        sep = ", ";
        s += ts(x);
    }
    return s + "}";
}
template<class A, class B>
sts(pair<A, B> p) {return "(" + ts(p.first) + ", " + ts(p.second) + ")";}
void dbgPrint() {cerr << endl;}
template<class A, class... B>
void dbgPrint(A a, B... b) {
    cerr << " " << ts(a);
    dbgPrint(b...);
}
#define dbg(...) cerr << "line #" << __LINE__ << "[" << #__VA_ARGS__ << "]:", dbgPrint(__VA_ARGS__)
