#ifndef noteqcheck_h_
#define noteqcheck_h_

bool noteqcheck(long long number, const std::vector<long long>& vec) {
    for (auto i: vec) {
        if (i == number) {
            return true;
        }
    }
    return false;
}

#endif