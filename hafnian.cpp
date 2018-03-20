#define T(x) ((x)*((x)-1)/2)
#define S 1
#define J (1<<S)
#define TYPE int

#include <iostream>
#include <vector>
#include <string>
#include <pthread.h>

using namespace std;

struct H {
    int s, w, t;
    TYPE *b, *g;
};

void *solve(void *a);
void hafnian(TYPE *b, int s, TYPE *g, int w, int t);

int n, m, ti = 0;
TYPE r[J] = {0};
pthread_t pool[J];

int main(void) {
    vector<int> a;
    string s;
    getline(cin, s);

    for (int i = 0; i < s.size(); i++)
        if (s[i] == '0' || s[i] == '1')
            a.push_back((s[i-1] == '-' ? -1 : 1)*(s[i] - '0'));

    for (n = 1; 4*n*n < a.size(); n++);
    m = n+1;

    TYPE z[T(2*n)*m] = {0}, g[m] = {0};

    for (int j = 1; j < 2*n; j++)
        for (int k = 0; k < j; k++)
            z[(T(j)+k)*m] = a[j*2*n+k];
    g[0] = 1;

    hafnian(z, 2*n, g, 1, -1);

    TYPE h = 0;
    for (int t = 0; t < ti; t++) {
        pthread_join(pool[t], NULL);
        h += r[t];
    }

    cout << h << endl;

    return 0;
}

void *solve(void *a) {
    H *p = reinterpret_cast<H*>(a);
    hafnian(p->b, p->s, p->g, p->w, p->t);
    delete[] p->b;
    delete[] p->g;
    delete p;
    return NULL;
}

void hafnian(TYPE *b, int s, TYPE *g, int w, int t) {
    if (t == -1 && (n < S || s/2 == n-S)) {
        H *p = new H;
        TYPE *c = new TYPE[T(s)*m], *e = new TYPE[m];
        copy(b, b+T(s)*m, c);
        copy(g, g+m, e);
        p->b = c;
        p->s = s;
        p->g = e;
        p->w = w;
        p->t = ti;
        pthread_create(pool+ti, NULL, solve, p);
        ti++;
    }
    else if (s > 0) {
        TYPE c[T(s-2)*m], e[m];
        copy(b, b+T(s-2)*m, c);
        hafnian(c, s-2, g, -w, t);
        copy(g, g+m, e);

        for (int u = 0; u < n; u++) {
            TYPE *d = e+u+1,
                  p = g[u], *x = b+(T(s)-1)*m;
            for (int v = 0; v < n-u; v++)
                d[v] += p*x[v];
        }

        for (int j = 1; j < s-2; j++)
            for (int k = 0; k < j; k++)
                for (int u = 0; u < n; u++) {
                    TYPE *d = c+(T(j)+k)*m+u+1,
                          p = b[(T(s-2)+j)*m+u], *x = b+(T(s-1)+k)*m,
                          q = b[(T(s-2)+k)*m+u], *y = b+(T(s-1)+j)*m;
                    for (int v = 0; v < n-u; v++)
                        d[v] += p*x[v] + q*y[v];
                }

        hafnian(c, s-2, e, w, t);
    }
    else
        r[t] += w*g[n];
}
