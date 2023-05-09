namespace moc {

void hello();

typedef unsigned char byte;

class bytes {
  int length;
  byte* _bytes;

 public:
  bytes(int _len);
  bytes(int _len, byte* _b);
  ~bytes();
  byte& operator[](int _i);
  inline int size() { return length; }
};
}  // namespace moc