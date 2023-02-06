
auto CIC::serialize(serializer& s) -> void {
  s(fifo.bits);
  s(seed);
  s(checksum);
  s(type);
  s(region);
  s(state);
  s(challengeAlgo);
}
