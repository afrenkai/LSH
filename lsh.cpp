#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <random>
#include <bitset>

using namespace std;

using Vec  = vector<double>;
using HashCode = bitset<32>;

class LSH {
    int nhashes;
    int dim;
    vector<Vec> randomplane;
}

public:
    LSH(int nhashes, int dim):
        nhashes(nhashes), dim(dim) {
            makeHyperplane
        }

    void makeHyperplane() {
        random_device rd;
        mt1997 gen(rd());
        normal_distribution<> dist(0.0, 1.0);

        for (int i = 0; i < nhashes, ++i) {
            Vec plane(dim);
            for (int j = 0; j < dim; ++j) {
                plane[j] = dist(gen)
            }
            randomplane.push_back(plane);
        }
    }

    double dot(const Vec& a, const Vec& b) const {
        double res = 0.0;
        for (int i = 0; i < a.size(); ++i) {
            res += a[i] * b[i];
        }
        return res;
    }

    HashCode getHash(const Vec& vec) const {
        HashCode code;
        for (int i = 0; i < nhashes; ++i) {
            code[i] = dot(vec, randomplane[i]) >= 0;
        }
        return code;
    };

int main {
    int nhashes = 10;
    int dims = 5;
    LSH lsh(nhashes, dim);
    Vector vec1 = {1.0, 0.0, 1.0, 0.0, 1.0};
    Vector vec2 = {0.9, 0.1, 1.1, -0.1, 1.0};
    Vector vec3 = {-1.0, -1.0, -1.0, -1.0, -1.0};
    HashCode h1 = lsh.getHash(vec1);
    HashCode h2 = lsh.getHash(vec2);
    HashCode h3 = lsh.getHash(vec3);
    cout << "Hash 1: " << h1 << endl;
    cout << "Hash 2: " << h2 << endl;
    cout << "Hash 3: " << h3 << endl;

    cout << "Hamming distance (vec1 vs vec2): " << (h1 ^ h2).count() << endl;
    cout << "Hamming distance (vec1 vs vec3): " << (h1 ^ h3).count() << endl;

    return 0;
}
