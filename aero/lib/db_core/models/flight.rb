require 'db_core/models/model'

class Flight < Model
  attr_accessor :company, :crew

  def Flight.create_table(connection)
    begin
      connection.do("
CREATE TABLE flights(
  id serial PRIMARY KEY,
  code varchar(16) UNIQUE NOT NULL,
  arrival_date timestamp NOT NULL,
  departure_date timestamp NOT NULL,
  arrival_place text NOT NULL,
  departure_place text NOT NULL,
  arrival_airport text NOT NULL,
  departure_airport text NOT NULL,
  company_id integer REFERENCES companies(id) NOT NULL,
  is_departure boolean NOT NULL DEFAULT true,
  crew_id integer REFERENCES crews(id)
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end

  def initialize(attributes = {})
    @company = nil
    @crew = nil
    @attributes = {}
    attributes.each do |k, v|
      @attributes[k.to_sym] = v unless v.nil? or v == ''
    end
  end

  def company_name()
    @company.nil? ? '&nbsp;' : @company[:name]
  end

  def Flight.find_all(connection, departure = nil)
    query = []
    res = []
    if departure.nil?
      query = ["SELECT * FROM flights
          ORDER BY departure_place, departure_date"]
    else
      query = ["SELECT * FROM flights
          WHERE is_departure = ?
          ORDER BY departure_place, departure_date", departure]
    end
    connection.select_all(*query) do |r|
      f = self.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      f.company = Company.find_first(connection, f[:company_id]) unless f[:company_id].nil?
      f.crew = Crew.find_first(connection, f[:crew_id]) unless f[:crew_id].nil?
      res << f
    end
    return res
  end

  def Flight.find_first(connection, id)
    id = id.to_i
    query = ["SELECT * FROM #{table_name()} WHERE id = ?", id]
    r = connection.select_one(*query)
    return nil if r.nil?
    f = self.new
    r.column_names.each do |c|
      f[c.to_sym] = r[c]
    end
    f.company = Company.find_first(connection, f[:company_id]) unless f[:company_id].nil?
    f.crew = Crew.find_first(connection, f[:crew_id]) unless f[:crew_id].nil?
    return f
  end
  def destroy(connection)
    unless self[:id].nil?
      connection.do("DELETE FROM #{table_name()} CASCADE WHERE id = ?", self[:id])
    end
  end
  def Flight.find_all_by_crew_id(connection, id)
    query = []
    res = []
    query = ["SELECT * FROM flights WHERE crew_id = ? ORDER BY departure_place, departure_date", id]
    connection.select_all(*query) do |r|
      f = self.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      f.company = Company.find_first(connection,
      f[:company_id]) unless f[:company_id].nil?
      f.crew = Crew.find_first(connection, f[:crew_id]) unless f[:crew_id].nil?
      res << f
    end
    return res
  end
end