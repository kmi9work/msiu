require 'db_core/models/model'

class Passenger < Model
  attr_reader :flight
  attr_writer :flight

  def Passenger.create_table(connection)
    begin
      connection.do("
CREATE TABLE passengers(
  id serial PRIMARY KEY,
  surname text NOT NULL,
  name text NOT NULL,
  patronymic text NOT NULL,
  npass_i text NOT NULL,
  npass_e text NOT NULL,
  info text,
  flight_id integer REFERENCES flights(id) NOT NULL
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end

  def initialize(attributes = {})
    @flight = nil
    @attributes = {
      :id => nil,
      :surname => nil,
      :name => nil,
      :patronymic => nil,
      :npass_i => nil,
      :npass_e => nil,
      :patronymic => nil,
      :flight_id => nil
    }
    attributes.each do |k, v|
      @attributes[k.to_sym] = v unless v.nil? or v == ''
    end
  end
def flight_name()
    @flight.nil? ? '&nbsp;' : @flight[:code]
  end
 def Passenger.find_pas(connection, id)
    query = []
    res = []
      query = ["SELECT * FROM passengers where flight_id=? ORDER BY flight_id", id]
    connection.select_all(*query) do |r|
      f = self.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      f.flight = Flight.find_first(connection,
        f[:flight_id]) unless f[:flight_id].nil?
      res << f
    end
    return res
  end
  def Passenger.find_all(connection)
    query = []
    res = []
      query = ["SELECT * FROM passengers ORDER BY flight_id"]
    connection.select_all(*query) do |r|
      f = self.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      f.flight = Flight.find_first(connection,
        f[:flight_id]) unless f[:flight_id].nil?
      res << f
    end
    return res
  end
 
  def Passenger.find_first(connection, id)
    id = id.to_i
    query = ["SELECT * FROM #{table_name()} WHERE id = ?", id]
    r = connection.select_one(*query)
    return nil if r.nil?
    c = self.new
    r.column_names.each do |i|
      c[i.to_sym] = r[i]
    end
    c.flight = Flight.find_first(connection,
      c[:flight_id]) unless c[:flight_id].nil?
    return c
  end
  
  def Passenger.search(connection, params)
    if params.size < 1
      return nil
    else
      ans = []
      params.each do |key, value|
        if key == 'surname' or key == 'name' or key == 'patronymic' or key == 'npass_i' or key == 'npass_e'
          query = ["SELECT * FROM passengers WHERE #{key} = ?", value[0]]
          connection.select_all(*query) do |r|
            f = self.new
            r.column_names.each do |c|
              f[c.to_sym] = r[c]
            end
            f.flight = Flight.find_first(connection, f[:flight_id]) unless f[:flight_id].nil?
            ans << f
          end
        end
        if key == 'code'
          query = ["SELECT * FROM passengers WHERE flight_id = ?", value[0]]
          connection.select_all(*query) do |r|
            f = self.new
            r.column_names.each do |c|
              f[c.to_sym] = r[c]
            end
            f.flight = Flight.find_first(connection, f[:flight_id]) unless f[:flight_id].nil?
            ans << f
          end
        end
      end
      if ans.size < 1
        return nil 
      else
        return ans
      end
    end
  end
end
