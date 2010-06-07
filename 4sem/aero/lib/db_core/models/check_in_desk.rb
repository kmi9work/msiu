require 'db_core/models/model'

class CheckInDesk < Model
  def CheckInDesk.create_table(connection)
    begin
      connection.do("
CREATE TABLE check_in_desks(
    id serial PRIMARY KEY,
    name varchar(16) UNIQUE NOT NULL,
    description text
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
      :name => nil,
      :description => nil
    }

    attributes.each do |k, v|
      @attributes[k] = v
    end
  end

  def self.table_name
    "check_in_desks"
  end

  def self.find_all_for_select(connection, flight)
    query = []
    res  = []

    query = ["SELECT * FROM check_in_desks WHERE id NOT IN (SELECT cd.id FROM check_in_desks cd JOIN check_in_desk_flights cdf ON (cdf.check_in_desk_id = cd.id) WHERE cdf.flight_id = ?)", flight[:id]]

    connection.select_all(*query) do |r|
      f = CheckInDesk.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      res << f
    end
    return res
  end

  def flights(connection)
    query = []
    res  = []

    query = ["SELECT f.* FROM flights f JOIN check_in_desk_flights cdf ON (cdf.flight_id = f.id) WHERE cdf.check_in_desk_id = ?", self[:id]]

    connection.select_all(*query) do |r|
      f = Flight.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      res << f
    end
    return res
  end
end

