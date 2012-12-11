class Packet < OpenStruct
  @@protocol = YAML::load(File.open(File.expand_path('../../../config/protocol.yml', __FILE__)))

#   def write(socket)
#     socket.write_uint16(self.size)
#     socket.write_uint8(self.type)
# # !!!!
#   end

  def initialize(socket)
    super()
    read!(socket)
  end

  def read!(socket)
    read_head!(socket)
    read_body!(socket)
    self
  end

  private

  def read_head!(socket)
    @@protocol['packet_head'].each_pair do |key, val|
      self.send("#{key}=", socket.read_by_type(val))
    end
  end

  def read_body!(socket)
    packet_type = @@protocol['packet_type'][type]
    @@protocol['packet'][packet_type].each do |key, val|
      self.send("#{key}=", socket.read_by_type(val))
    end
  end

  def make_body!(params)
    
  end

  def make_head!(size = 0, type = 0)
    # @@protocol['packet_head'].each_pair do |key, val|
    #   self.send("#{key}=", socket.read_by_type(val))
    # end
  end
end