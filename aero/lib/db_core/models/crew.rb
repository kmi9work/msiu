require 'db_core/models/model'
require 'db_core/models/fly_personal'
class Crew < Model
  attr_accessor :pilot, :stuard1, :stuard2, :second_pilot, :mechanic, :flight
  def Crew.create_table(connection)
    begin
      connection.do("
CREATE TABLE crews(
  id serial PRIMARY KEY,
  pilot_id integer REFERENCES fly_personals(id) NOT NULL,
  stuard1_id integer REFERENCES fly_personals(id) NOT NULL,
  stuard2_id integer REFERENCES fly_personals(id) NOT NULL,
  mechanic_id integer REFERENCES fly_personals(id) NOT NULL,
  second_pilot_id integer REFERENCES fly_personals(id) NOT NULL,
  is_busy boolean DEFAULT false,
  flight_id integer
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end

  def initialize(attributes = {})
    @attributes = {
      :id => nil,
      :pilot_id => nil, 
      :stuard1_id => nil,
      :stuard2_id => nil,
      :mechanic_id => nil,
      :second_pilot_id => nil,
      :is_busy => nil,
      :flight_id => nil
    }
    attributes.each do |k, v|
      @attributes[k.to_sym] = v unless v.nil? or v == ''
    end
  end
  def Crew.find_by_flight_id(connection, flight_id)
    flight_id = flight_id.to_i
    query = ["SELECT * FROM #{table_name()} WHERE flight_id = ?", flight_id]
    r = connection.select_one(*query)
    return nil if r.nil?
    f = self.new
    r.column_names.each do |c|
      f[c.to_sym] = r[c]
    end
    f.pilot = FlyPersonal.find_first(connection,f[:pilot_id]) unless f[:pilot_id].nil?
    f.second_pilot = FlyPersonal.find_first(connection,f[:second_pilot_id]) unless f[:second_pilot_id].nil?
    f.stuard1 = FlyPersonal.find_first(connection,f[:stuard1_id]) unless f[:stuard1_id].nil?
    f.stuard2 = FlyPersonal.find_first(connection,f[:stuard2_id]) unless f[:stuard2_id].nil?
    f.mechanic = FlyPersonal.find_first(connection,f[:mechanic_id]) unless f[:mechanic_id].nil?
    f.flight = f[:flight_id].nil? ? nil : Flight.find_first(connection, f[:flight_id])
    return f
  end

  def Crew.find_first(connection, id)
    id = id.to_i
    query = ["SELECT * FROM crews WHERE id = ?", id]
    r = connection.select_one(*query)
    return nil if r.nil?
    o = self.new
    r.column_names.each do |c|
      o[c.to_sym] = r[c]
    end
    o.pilot = FlyPersonal.find_first(connection,o[:pilot_id]) unless o[:pilot_id].nil?
    o.second_pilot = FlyPersonal.find_first(connection,o[:second_pilot_id]) unless o[:second_pilot_id].nil?
    o.stuard1 = FlyPersonal.find_first(connection,o[:stuard1_id]) unless o[:stuard1_id].nil?
    o.stuard2 = FlyPersonal.find_first(connection,o[:stuard2_id]) unless o[:stuard2_id].nil?
    o.mechanic = FlyPersonal.find_first(connection,o[:mechanic_id]) unless o[:mechanic_id].nil?
    o.flight = o[:flight_id].nil? ? nil : Flight.find_first(connection, o[:flight_id])
    return o
  end

  
  def save(connection)
    query = '' 
    params = []
    if self[:id].nil?
      query = "INSERT INTO crews(" +
        (@attributes.keys - [:id]).join(', ') + ') VALUES(' +
        (@attributes.keys - [:id]).map{ |k| '?' }.join(', ') + ') RETURNING id'
      params = (@attributes.keys - [:id]).map{ |k| self[k] }
    else
      query = "UPDATE crews SET " +
        (@attributes.keys - [:id]).map{ |k| "#{k} = ?" }.join(', ') +
        ' WHERE id = ? RETURNING id'
      params = (@attributes.keys - [:id]).map{ |k| self[k] } << self[:id]
    end
    rs = connection.select_one(query, *params)
    self[:id] = rs[0].to_i
  end

  def Crew.find_all(connection)
    res = []
    query = ["SELECT * FROM crews"]
    connection.select_all(*query) do |r|
      o = self.new
      r.column_names.each do |c|
        o[c.to_sym] = r[c]
      end
    o.pilot = FlyPersonal.find_first(connection,o[:pilot_id]) unless o[:pilot_id].nil?
    o.second_pilot = FlyPersonal.find_first(connection,o[:second_pilot_id]) unless o[:second_pilot_id].nil?
    o.stuard1 = FlyPersonal.find_first(connection,o[:stuard1_id]) unless o[:stuard1_id].nil?
    o.stuard2 = FlyPersonal.find_first(connection,o[:stuard2_id]) unless o[:stuard2_id].nil?
    o.mechanic = FlyPersonal.find_first(connection,o[:mechanic_id]) unless o[:mechanic_id].nil?
    o.flight = o[:flight_id].nil? ? nil : Flight.find_first(connection, o[:flight_id])
      res << o
    end
    return res
  end


end

