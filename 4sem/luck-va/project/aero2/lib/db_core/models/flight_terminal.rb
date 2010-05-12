require 'db_core/models/model'

class FlightTerminal < Model
  attr_accessor :terminal
  def FlightTerminal.create_table(connection)
    begin
      connection.do("
CREATE TABLE flight_terminals(
  id serial PRIMARY KEY,
  flight_id integer REFERENCES flights(id) NOT NULL,
  terminal_id integer REFERENCES terminals(id) NOT NULL,
  info text,
  UNIQUE(flight_id, terminal_id)
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
      :flight_id => nil,
      :terminal_id => nil,
      :info => nil
    }
    attributes.each do |k, v|
      @attributes[k] = v
    end
  end
  
  def FlightTerminal.find_by_id(connection, id)
    id = id.to_i
    query = ["SELECT * FROM flight_terminals WHERE id = ?", id]
    r = connection.select_one(*query)
    return nil if r.nil?
    o = self.new
    r.column_names.each do |c|
      o[c.to_sym] = r[c]
    end
    o.terminal = Terminal.find_by_id(connection, o[:terminal_id])
    return o
  end
  
  def FlightTerminal.find_all_by_flight_id(connection, flight_id)
    query = []
    res = []
    query = ["SELECT * FROM flight_terminals WHERE flight_id = ?", flight_id]
    connection.select_all(*query) do |r|
      o = self.new
      r.column_names.each do |c|
        o[c.to_sym] = r[c]
      end
      o.terminal = Terminal.find_by_id(connection, o[:terminal_id])
      res << o
    end
    return res
  end
end
