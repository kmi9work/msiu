require 'db_core/models/model'

class FlightStatus < Model
  STATUSES = {0 => 'отменен', 1 => 'задержан', 2 => 'вылетел', 3 => 'сел'}

  def FlightStatus.create_table(connection)
    begin
      connection.do("
CREATE TABLE flight_statuses(
  id serial PRIMARY KEY,
  flight_id integer REFERENCES flights(id) NOT NULL,
  status integer NOT NULL CONSTRAINT status_ck CHECK(status in(0, 1, 2, 3)),
  event_date timestamp NOT NULL,
  UNIQUE(flight_id, event_date)
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end
  def FlightStatus.table_name()
    return 'flight_statuses'
  end
  def Model.find_all_by_id(connection, id)
    query = []
    res = []
    query = ["SELECT * FROM flight_statuses WHERE flight_id = id"]
    connection.select_all(*query) do |r|
      o = self.new
      r.column_names.each do |c|
        o[c.to_sym] = r[c]
      end
      res << o
    end
    return res
  end
  
end
