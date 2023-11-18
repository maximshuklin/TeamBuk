//before int main()

template <class T = int> inline T readInt(); // skip spaces, read signed int
template <class T> inline void writeInt( T x );
inline void writeChar( int x ); // you may use putchar() instead of it
inline void flush();

// after int main()

/** Read */
 
static const int buf_size = 4096;
 
inline int getchar_fast() { // you may use getchar() instead of it
  static char buf[buf_size];
  static int len = 0, pos = 0;
  if (pos == len)
    pos = 0, len = fread(buf, 1, buf_size, stdin);
  if (pos == len)
    return -1;
  return buf[pos++];
}
 
inline int readChar() {
  int c = getchar_fast();
  while (c <= 32)
    c = getchar_fast();
  return c;
}
 
template <class T>
inline T readInt() {
  int s = 1, c = readChar();
  T x = 0;
  if (c == '-')
    s = -1, c = getchar_fast();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getchar_fast();
  return s == 1 ? x : -x;
}
 
/** Write */
 
static int write_pos = 0;
static char write_buf[buf_size];
 
inline void writeChar( int x ) {
  if (write_pos == buf_size)
    fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
  write_buf[write_pos++] = x;
}
 
inline void flush() {
  if (write_pos)
    fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
}
 
template <class T>
inline void writeInt( T x ) {
  if (x < 0)
    writeChar('-'), x = -x;
 
  char s[24];
  int n = 0;
  while (x || !n)
    s[n++] = '0' + x % 10, x /= 10;
  while (n--)
    writeChar(s[n]);
}
