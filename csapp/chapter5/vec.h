
typedef int data_t;

/* Create abstract data type for vector */
typedef struct {
    long len;
    data_t *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(long len);

int get_vec_element(vec_ptr v, long index, data_t *dest);

data_t* get_vec_start(vec_ptr v);

long vec_length(vec_ptr v);
