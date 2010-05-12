require 'db_core/models/model'

class FlightCheckInDesk < Model
  attr_accessor :check_in_desk
  def FlightCheckInDesk.create_table(connection)
    begin
      connection.do("
CREATE TABLE flight_check_in_desks(
  id serial PRIMARY KEY,
  flight_id integer REFERENCES flights(id) NOT NULL,
  check_in_desk_id integer REFERENCES check_in_desks(id) NOT NULL,
  info text,
  UNIQUE(flight_id, check_in_desk_id)
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end
  def FlightCheckInDesk.find_all_by_flight_id(connection, flight_id)
    query = []
    res = []
    query = ["SELECT * FROM flight_check_in_desks WHERE flight_id = ?", flight_id]
    connection.select_all(*query) do |r|
      o = self.new
      r.column_names.each do |c|
        o[c.to_sym] = r[c]
      end
      o.check_in_desk = CheckInDesk.find_by_id(connection, o[:check_in_desk_id])
      res << o
    end
    return res
  end
  
  def FlightCheckInDesk.find_by_id(connection, id)
    id = id.to_i
    query = ["SELECT * FROM flight_check_in_desks WHERE id = ?", id]
    r = connection.select_one(*query)
    return nil if r.nil?
    o = self.new
    r.column_names.each do |c|
      o[c.to_sym] = r[c]
    end
    o.check_in_desk = CheckInDesk.find_by_id(connection, o[:check_in_desk_id])
    return o
  end
  
end
