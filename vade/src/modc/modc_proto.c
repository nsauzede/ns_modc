#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

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
	allocator_cb proc;
} allocator_t;

void *default_allocator_cb() {
	return 0;
}

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

//str_buf str_buf_make(int size, allocator alloc) {
str_buf str_buf_make(int size) {
	return (str_buf){calloc(1, size), 0, size};
}
void str_buf_delete(str_buf sb) {
	if (sb.data) {
		free(sb.data);
	}
}
void str_buf_append(str_buf *sb, str s) {
	if (sb->capacity >= sb->size + s.size) {
		memcpy(sb->data + sb->size, s.data, s.size);
		sb->size += s.size;
	}
}
void str_buf_insert(str_buf *, str, int);
void str_buf_remove(str_buf *, int, int);
str str_buf_str(str_buf sb) {
	return (str){sb.data, sb.size};
}

str cstr(char *cs) {
	str s = {0};
	s.data = cs;
	s.size = strlen(cs);
	return s;
}

bool str_valid(str s) {
	return (s.data != 0);
}
bool str_match(str a, str b);
bool str_contains(str haystack, str needle);
str str_sub(str src, int begin, int end);
str str_find_first(str haystack, str needle) {
	str result = {0};
	if (!str_valid(haystack) || !str_valid(needle) || needle.size > haystack.size) {
		return result;
	}
	for (int i = 0; i <= haystack.size - needle.size; i++) {
		if (!memcmp(haystack.data + i, needle.data, needle.size)) {
			result.data = haystack.data + i;
			result.size = needle.size;
			break;
		}
	}
	return result;
}
str str_find_last(str haystack, str needle);
str str_remove_prefix(str src, str prefix);
str str_remove_suffix(str src, str suffix);

#define for_str_split(iter, src, split_by)						\
	for (										\
		str macro_var(src_) = src,						\
		iter = str_pop_first_split(&macro_var(src_), split_by),			\
		macro_var(split_by_) = split_by;					\
											\
		str_valid(iter);							\
											\
		iter = str_pop_first_split(&macro_var(src_), macro_var(split_by_))	\
		)

str str_pop_first_split(str* src, str split_by) {
	str s = *src;
	str n = str_find_first(*src, split_by);
	if (str_valid(n)) {
		s.data = src->data;
		s.size = n.data - s.data;
		src->data += s.size + 1;
		src->size -= s.size + 1;
	} else {
		src->data = 0;
		src->size = 0;
	}
	return s;
}

void print(str s) {
	if (!str_valid(s)) {
		return;
	}
	for (int i = 0; i < s.size; i++) {
		putchar(s.data[i]);
	}
}

void panic(const char *msg) {
	printf("\n%s\n", msg);
	exit(1);
}

void print_(str s, ...) {
	if (!str_valid(s)) {
		return;
	}
	va_list args;
	va_start(args, s);
	int perc = 0;
	int obrace = 0;
	int cbrace = 0;
	int opt = 0;
	int debug = 0;
	for (int i = 0; i < s.size; i++) {
		char c = s.data[i];
		if (c == '%') {
			if (perc) {
				perc = 0;
			} else {
				perc = 1;
				continue;
			}
		} else if (c == '{') {
			if (obrace) {
				obrace = 0;
			} else {
				obrace = 1;
				continue;
			}
		} else if (c == '}') {
			if (obrace) {
				str a = va_arg(args, str);
				if (opt) {
					if (debug) {
						putchar('"');
						print(a);
						putchar('"');
					} else {
						print(a);
					}
				} else {
					print(a);
				}
				obrace = 0;
				continue;
			} else {
				if (cbrace) {
					cbrace = 0;
				} else {
					cbrace = 1;
					continue;
				}
			}
		}
		if (perc) {
			perc = 0;
			if (c == 'd') {
				int d = va_arg(args, int);
				printf("%d", d);
			} else {
				panic("invalid cfmt");
			}
			continue;
		}
		if (obrace) {
			if (c == ':') {
				if (opt) {
					panic("invalid fmt: expected `}`");
				}
				opt = 1;
			} else if (c == '?') {
				if (!opt) {
					panic("invalid fmt: expected `}`");
				}
				debug = 1;
			} else {
				panic("invalid fmt: expected `}`");
			}
			continue;
		}
		putchar(c);
	}
	va_end(args);
}

#define println_(s, ...) do{print_(s, __VA_ARGS__);putchar('\n');}while(0)

void println(str s) {
	print(s);
	putchar('\n');
}

typedef struct cat{} cat;
void print_cat(cat *);

int modc_proto() {
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
	printf("date=");println(date);
	print(cstr("find_first="));
	println(str_find_first(date, cstr("7/02")));
	for_str_split(it, date, cstr("/")) {
		println(it);
	}
	str year = str_pop_first_split(&date, cstr("/"));
	str month = str_pop_first_split(&date, cstr("/"));
	str day = str_pop_first_split(&date, cstr("/"));
	printf("year=");println(year);
	printf("month=");println(month);
	printf("day=");println(day);
	str hour = str_pop_first_split(&date, cstr("/"));
	printf("hour=");println(hour);

	str s = cstr("{OPT}");
	println_(cstr("Hello world! {{ }} {} %d"), s, 42);
	println_(cstr("Hello world! {{}} {:} %d"), s, 42);
	println_(cstr("Hello world! {{ }} {:?} %d"), s, 42);

//	str_buf sb = str_buf_make(16, default_allocator_cb);
	str_buf sb = str_buf_make(16);
	str_buf_append(&sb, cstr("str"));
	str_buf_append(&sb, cstr("buf"));
	printf("str_buf=[");
	print(str_buf_str(sb));
	printf("]\n");
	str_buf_delete(sb);

	return 0;
}
