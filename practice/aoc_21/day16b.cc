#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a;
    [&] {
        string s;
        s = "40541D900AEDC01A88002191FE2F45D1006A2FC2388D278D4653E3910020F2E2F3E24C007ECD7ABA6A200E6E8017F92C934CFA0E5290B569CE0F4BA5180213D963C00DC40010A87905A0900021B0D624C34600906725FFCF597491C6008C01B0004223342488A200F4378C9198401B87311A0C0803E600FC4887F14CC01C8AF16A2010021D1260DC7530042C012957193779F96AD9B36100907A00980021513E3943600043225C1A8EB2C3040043CC3B1802B400D3CA4B8D3292E37C30600B325A541D979606E384B524C06008E802515A638A73A226009CDA5D8026200D473851150401E8BF16E2ACDFB7DCD4F5C02897A5288D299D89CA6AA672AD5118804F592FC5BE8037000042217C64876000874728550D4C0149F29D00524ACCD2566795A0D880432BEAC79995C86483A6F3B9F6833397DEA03E401004F28CD894B9C48A34BC371CF7AA840155E002012E21260923DC4C248035299ECEB0AC4DFC0179B864865CF8802F9A005E264C25372ABAC8DEA706009F005C32B7FCF1BF91CADFF3C6FE4B3FB073005A6F93B633B12E0054A124BEE9C570004B245126F6E11E5C0199BDEDCE589275C10027E97BE7EF330F126DF3817354FFC82671BB5402510C803788DFA009CAFB14ECDFE57D8A766F0001A74F924AC99678864725F253FD134400F9B5D3004A46489A00A4BEAD8F7F1F7497C39A0020F357618C71648032BB004E4BBC4292EF1167274F1AA0078902262B0D4718229C8608A5226528F86008CFA6E802F275E2248C65F3610066274CEA9A86794E58AA5E5BDE73F34945E2008D27D2278EE30C489B3D20336D00C2F002DF480AC820287D8096F700288082C001DE1400C50035005AA2013E5400B10028C009600A74001EF2004F8400C92B172801F0F4C0139B8E19A8017D96A510A7E698800EAC9294A6E985783A400AE4A2945E9170";
        // cin >> s;
        for (auto c : s) {
            int x = (c <= '9') ? (c - '0') : (c - 'A' + 10);
            for (int i = 3; i >= 0; --i) {
                a.push_back(x >> i & 1);
            }
        }
    }();
    for (auto x : a) {
        cout << x;
    }
    cout << "\n";
    int i = 0;
    auto read = [&](int l) -> long long {
        long long x = 0;
        l += i;
        while (i < l) {
            x = x << 1 | a[i];
            ++i;
        }
        return x;
    };
    function<long long(int)> rp = [&](int align) -> long long {
        int oi = i;
        auto v = read(3);
        (void)v;
        auto t = read(3);
        long long x = 0;
        if (t == 4) {
            while (1) {
                auto b = read(1);
                x = x << 4 | read(4);
                if (!b) {
                    break;
                }
            }
        } else {
            auto lt = read(1);
            vector<long long> p;
            if (lt == 0) {
                auto lsp = read(15);
                int oi2 = i;
                while (i - oi2 < lsp) {
                    p.push_back(rp(0));
                }
            } else {
                auto nsp = read(11);
                for (int spi = 0; spi < nsp; ++spi) {
                    p.push_back(rp(0));
                }
            }
            switch (t) {
                case 0:
                    x = reduce(p.begin(), p.end());
                    break;
                case 1:
                    x = 1;
                    for (auto y : p) {
                        x *= y;
                    }
                    break;
                case 2:
                    x = LLONG_MAX / 2;
                    for (auto y : p) {
                        x = min(x, y);
                    }
                    break;
                case 3:
                    x = 0;
                    for (auto y : p) {
                        x = max(x, y);
                    }
                    break;
                case 5:
                    x = p[0] > p[1];
                    break;
                case 6:
                    x = p[0] < p[1];
                    break;
                case 7:
                    x = p[0] == p[1];
                    break;
            }
        }
        while (align && (i - oi) % 4) {
            ++i;
        }
        return x;
    };
    cout << rp(1) << "\n";
}
