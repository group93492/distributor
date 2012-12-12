class String
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

  def write_by_type(value, type)
    # TODO: add check for non-existing method
    self.method("write_#{type}").call(value)
  end

  alias_method :write_string, :write_qbytearray
end
