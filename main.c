#include <stdbool.h>
#include <stdio.h>
#include <string.h>

float minf(float a, float b) {
	return a < b ? a : b;
}

float mini(int a, int b) {
	return a < b ? a : b;
}

void dummy(void){}

#define min(a, b) _Generic((a), float: minf(a, b), int: mini(a, b))

#define concat(a,b) a ## b

#define macro_var(name) concat(name, __LINE__)

#define defer(start, end) for(			\
	int macro_var(_i_) = (start, 0);	\
						\
	!macro_var(_i_);			\
						\
	(macro_var(_i_) += 1), end		\
	)

#define for_str_split(iter, src, split_by)						\
	for (										\
		str macro_var(src_) = src,						\
		iter = str_pop_first_split(&macro_var(src_), split_by),			\
		macro_var(split_by_) = split_by;					\
											\
		str_valid(macro_var(src_));						\
											\
		iter = str_pop_first_split(&macro_var(src_), macro_var(split_by_))	\
		)

#define scope(end) defer(dummy(),end)

void begin() {
	printf("begin\n");
}

void end() {
	printf("end\n");
}

void closure(int num) {
	printf("%d\n", num);
}

typedef union hmm_vec2 {
	struct {float x, y;};
	struct {float u, v;};
	struct {float left, right;};
	struct {float width, height;};
	float e[2];
} hmm_vec2;

typedef struct file_contents_t {
	int valid;
	char *data;
	int size;
} file_contents_t;

typedef struct image_t {
	int valid;
	char *pixels;
	int width, height;
} image_t;

file_contents_t read_file_contents(const char *f) {
	file_contents_t fc = {0};
	if (f) {
		fc.valid = 1;
	}
	return fc;
}

image_t load_image_from_file_contents(file_contents_t fc) {
	image_t i = {0};
	if (fc.valid) {
		i.valid = 1;
	}
	return i;
}

struct allocator;
typedef void *(*allocator_cb)(struct allocator *this_allocator, int amount_to_alloc, void *ptr_to_free);
typedef struct allocator {
	void *user_data;
	void *(*proc)(struct allocator *this_allocator, int amount_to_alloc, void *ptr_to_free);
} allocator_t;

typedef struct str {
	char *data;
	int size;
} str;

typedef struct str_buf {
	char *data;
	int size;
	int capacity;
	allocator_cb allocator;
} str_buf;

str_buf str_buf_make(int size, allocator_cb allocator);
void str_buf_append(str_buf *, str);
void str_buf_insert(str_buf *, str, int);
void str_buf_remove(str_buf *, int, int);
str str_buf_str(str_buf);

str cstr(char *cs) {
	str s = {0};
	s.data = cs;
	s.size = strlen(cs);
	return s;
}

bool str_valid(str s) {
	return !(s.data != 0);
}
bool str_match(str a, str b);
bool str_contains(str haystack, str needle);
str str_sub(str src, int begin, int end);
str str_find_first(str haystack, str needle);
str str_find_last(str haystack, str needle);
str str_remove_prefix(str src, str prefix);
str str_remove_suffix(str src, str suffix);

typedef struct cat{} cat;
void print_cat(cat *);
//logger_register_printer("cat", print_cat);
//cat c = ;
//log("Cat: {cat}", c);

str str_pop_first_split(str* src, str split_by) {
	str s = cstr("");
	
	return s;
}

#define str_pop_first_split_(src, split_by)				\
	_Generic(split_by,						\
	const char*: str_pop_first_split_impl(src, cstr(split_by)),	\
	char *: str_pop_first_split_impl(src, cstr(split_by)),		\
	default: str_pop_first_split_impl(src, split_by))

void println(str s) {
	printf("%s\n", s.data);
}

int main() {
//	logger_register_printer("cat", print_cat);
//	cat c = ;
//	log("Cat: {cat}", c);

	defer(begin(), end()) {
		printf("Hello world!\n");
	}
	int answer = 42;
	scope(closure(answer)) {
		printf("testing closure: ");
	}
	hmm_vec2 v = {.y=42};
	printf("float=%f\n", v.e[1]);
	file_contents_t fc = read_file_contents("hello.dat");
	image_t img = load_image_from_file_contents(fc);
	if (!img.valid) {
		printf("Failed to load image\n");
	} else {
		printf("Succesfully loaded image\n");
	}
	str date = cstr("2021/07/02");
	for_str_split(it, date, cstr("/")) {
		println(it);
	}
	str year = str_pop_first_split(&date, cstr("/"));
	printf("year=");
	println(year);

	return 0;
}
