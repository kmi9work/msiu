require 'db_core/models/model'

class FlightTerminal < Model
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

  def FlightTerminal.table_name()
    return 'flight_terminals'
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
end
