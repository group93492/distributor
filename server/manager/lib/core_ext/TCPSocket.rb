class TCPSocket
  def get_packet
    # TODO: add connection timeout
    Packet.new(self)
  end

  # Type is mandatory argument.
  def send_packet(params)
    fail "type must be specified" if params['type'].nil?
    serialized_packet = Packet.serialize_packet(params)
    self << serialized_packet
    serialized_packet
  end

  def read_by_type(type)
    # TODO: add check for non-existing method
    self.method("read_#{type}").call
  end

  def write_by_type(value, type)
    # TODO: add check for non-existing method
    self.method("write_#{type}").call(value)
  end

  def read_uint8
    num = ""
    1.times {num << self.getbyte.to_s(16)}
    num.to_i(16)
  end

  def read_uint16
    num = ""
    2.times {num << self.getbyte.to_s(16)}
    num.to_i(16)
  end

  def read_uint32
    num = ""
    4.times {num << self.getbyte.to_s(16)}
    num.to_i(16)
  end

  def read_uint64
    num = ""
    8.times {num << self.getbyte.to_s(16)}
    num.to_i(16)
  end

  def read_qbytearray
    size = self.read_uint32
    if size == 0xFFFFFFFF
      nil
    else
      msg = ""
      size.times { msg << self.read_uint8.chr(Encoding::UTF_8) }
      msg
    end
  end

  def write_uint8(value)
    self << [value].pack("C")
  end

  def write_uint16(value)
    self << [value].pack("S>")
  end

  def write_uint32(value)
    self << [value].pack("L>")
  end

  def write_uint64(value)
    self << [value].pack("Q>")
  end

  def write_qbytearray(string)
    if string.nil?
      self << self.write_uint32(0xFFFFFFFF)
    else
      self.write_uint32(string.size)
      self << string
    end
  end

  def write_bool(bool)
    self << [bool.to_i].pack("C")
  end

  alias_method :write_string, :write_qbytearray
  alias_method :read_string, :read_qbytearray
end
