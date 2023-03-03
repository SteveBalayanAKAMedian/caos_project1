enum {
    N = 32,
    MY_DIVISION_BY_ZERO = 1,
    MY_OVERFLOW = 2,
    DIVISION_ERROR = 3,
};  // suppose int is a 32bit type

struct divmod_t {
    unsigned int l;
    unsigned long long m;
    int sh1;
    int sh2;
    int sign_d;
    unsigned int d;
};

struct divmod_t divmod_init(int b);

int div_const(struct divmod_t *divmod, int a);

int mod_const(struct divmod_t *divmod, int n);
