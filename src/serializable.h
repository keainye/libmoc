#include "iostream"

namespace moc {
class serializable {
 public:
  virtual char *to_bytes(int &_n) = 0;
  virtual void from_bytes(char *_b, int _n) = 0;
  virtual bool to_stream(std::ostream _s) = 0;
  virtual void from_stream(std::istream _s) = 0;
};
}