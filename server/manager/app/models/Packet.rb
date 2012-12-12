class Packet < OpenStruct
  @@protocol = YAML::load(File.open(File.expand_path('../../../config/protocol.yml', __FILE__)))

  def initialize(*args)
    super()
    case args.size
    when 0
    when 1
      read!(args.pop)
    end
  end

  # Read next packet from socket. Its type should be specified in protocol.yml
  def read!(socket)
    read_head!(socket)
    read_body!(socket)
    self
  end

  # Type is mandatory argument. Type should be in params.
  def self.serialize_packet(params)
    packet = Packet.new
    packet.make!(params)
    packet.serialize_packet
  end

  # Type is mandatory argument and it should be already specified.
  def serialize_packet
    fail "type should be specified" if self.type.nil?
    serialized_packet = ""
    @@protocol['packet'][self.type].each_pair do |field_name, field_type|
      serialized_packet.write_by_type(self.send(field_name), field_type)
    end
    # serialize head and add it to the begin of packet
    serialized_packet.prepend(serialize_head(serialized_packet))
    serialized_packet
  end

  # Type is mandatory argument.
  # Make packet in human readable format. Size field would be filled on sending.
  def make!(params = {})
    fail "type should be specified" if params['type'].nil?
    make_head!(params)
    make_body!(params)
    self
  end

  private

  # Type should be already specified.
  def serialize_head(serialized_body)
    fail "type should be specified" if self.type.nil?
    head = ""
    head_size_type = @@protocol['packet_head']['size']
    head_type_type = @@protocol['packet_head']['type']
    head.write_by_type(serialized_body.size, head_size_type)
    serialized_type = @@protocol['packet_type'].key(self.type)
    head.write_by_type(serialized_type, head_type_type)
    head
  end

  def read_head!(socket)
    @@protocol['packet_head'].each_pair do |key, val|
      self.send("#{key}=", socket.read_by_type(val))
    end
    self.type = @@protocol['packet_type'][self.type] # convert type id to human string
  end

  def read_body!(socket)
    @@protocol['packet'][self.type].each_pair do |key, val|
      self.send("#{key}=", socket.read_by_type(val))
    end
  end

  def make_body!(params = {})
    @@protocol['packet'][self.type].each_key do |key|
      self.send("#{key}=", params[key])
    end
  end

  def make_head!(params = {})
    @@protocol['packet_head'].each_key do |key|
      self.send("#{key}=", params[key])
    end
  end
end
