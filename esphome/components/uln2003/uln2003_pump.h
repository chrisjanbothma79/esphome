class ULN2003Pump : public Component, public switch_::Switch {
 public:
  void setup() override {
    pinMode(this->control_pin_, OUTPUT);
    digitalWrite(this->control_pin_, LOW);
  }

  void write_state(bool state) override {
    digitalWrite(this->control_pin_, state ? HIGH : LOW);
    publish_state(state);
  }

 protected:
  GPIOPin *control_pin_;
};
