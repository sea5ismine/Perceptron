#include <bits/stdc++.h>

using namespace std;

const int maxk = 20;
const int maxn = 30005;
const int maxc = 10;
const int maxt = 10005;
const int threshold = 500;
const double eps = 1e-8;
inline int dcmp(double x)
{
    if(fabs(x) < eps)
        return 0;
    return x > 0 ? 1 : -1;
}

struct Point
{
    double coor[maxk];
};
struct Node
{
    Point point;
    int id;
};

Node pt[maxn];
Node line[maxc];
Node test[maxt];
int n, k, c, t;

int main()
{
    while(scanf("%d %d %d %d", &n, &k, &c, &t) == 4)
    {
        freopen("TrainSamples.csv", "r", stdin);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < k; j++)
                scanf("%lf,", &pt[i].point.coor[j]);
        freopen("TrainLabels.csv", "r", stdin);
        for(int i = 0; i < n; i++)
            scanf("%d", &pt[i].id);
        for(int i = 0; i < c; i++)
        {
            line[i].id = i + 1;
            for(int j = 0; j <= k; j++)
                line[i].point.coor[j] = 1.0;
            for(int j = 0; j < n; j++)
                pt[j].point.coor[k] = pt[j].id == line[i].id ? 1 : -1;
            int pass = 0;
            while(pass < n - n / c - threshold)
            {
                pass = 0;
                for(int now = 0; now < n; now++)
                {
                    double tmp = 0.0;
                    for(int j = 0; j <= k; j++)
                        tmp += line[i].point.coor[j] * pt[now].point.coor[j];
                    if(dcmp(tmp) < 0)
                        for(int j = 0; j <= k; j++)
                            line[i].point.coor[j] += pt[now].point.coor[j];
                    pass += dcmp(tmp) >= 0 ? 1 : 0;
                }
            }
//            for(int j = 0; j <= k; j++)
//                printf("%.2f ", line[i].point.coor[j]);
//            puts("");
        }
        freopen("TestSamples.csv", "r", stdin);
        for(int i = 0; i < t; i++)
            for(int j = 0; j < k ; j++)
                scanf("%lf,", &test[i].point.coor[j]);
        freopen("TestLabels.csv", "r", stdin);
        for(int i = 0; i < t; i++)
            scanf("%d", &test[i].id);
        int ans = 0;
        for(int i = 0; i < t; i++)
        {
            vector <int> vec;
            test[i].point.coor[k] = 1;
            int rec = 0, loc;
            for(int j = 0; j < c; j++)
            {
                double tmp = 0.0;
                for(int l = 0; l <= k; l++)
                    tmp += line[j].point.coor[l] * test[i].point.coor[l];
                if(dcmp(tmp) >= 0)
                    rec++, vec.push_back(line[j].id);
            }
            for(int j = 0; j < vec.size(); j++)
                if(vec[j] == test[i].id)
                    ans++;
        }
        int train = 0;
        for(int i = 0; i < n; i++)
        {
            vector <int> vec;
            pt[i].point.coor[k] = 1;
            int rec = 0, loc;
            for(int j = 0; j < c; j++)
            {
                double tmp = 0.0;
                for(int l = 0; l <= k; l++)
                    tmp += line[j].point.coor[l] * pt[i].point.coor[l];
                if(dcmp(tmp) >= 0)
                    rec++, vec.push_back(line[j].id);
            }
            for(int j = 0; j < vec.size(); j++)
                if(vec[j] == pt[i].id)
                    train++;
        }
        printf("%d %d\n", ans, train);
    }
    return 0;
}
