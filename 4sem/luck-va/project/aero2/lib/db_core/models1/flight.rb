require 'db_core/models/model'

class Flight < Model
  attr_accessor :company
  attr_writer :statuses, :terminals, :check_in_desks
  
  def Flight.status(connection)
    res = []
    
    return res
  end
  
  def Flight.terminal(connection)
    res = []
    
    return res
  end
  
  def Flight.check_in_desk(connection)
    res = []
    
    return res
  end
  
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
  is_departure boolean NOT NULL DEFAULT true
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end

  def initialize(attributes = {})
    @company = nil
    @attributes = {
      :id => nil,
      :code => nil,
      :arrival_date => nil,
      :departure_date => nil,
      :arrival_place => nil,
      :departure_place => nil,
      :arrival_airport => nil,
      :departure_airport => nil,
      :company_id => nil,
      :is_departure => nil
    }
    attributes.each do |k, v|
      @attributes[k.to_sym] = v unless v.nil? or v == ''
    end
  end

  def company_name()
    @company.nil? ? '&nbsp;' : @company[:name]
  end

  def Flight.find_all(connection, departure = nil)
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
      f.company = Company.find_by_id(connection, f[:company_id]) unless f[:company_id].nil?
      f.statuses = []
      q = ["SELECT * FROM flight_statuses WHERE flight_id = ?", f[:id]]
      connection.select_all(*q){|r| f.statuses << r}
      f.terminals = []
      q = ["SELECT * FROM terminals WHERE id = (SELECT terminal_id FROM flight_terminals WHERE flight_id = ?)", f[:id]]
      connection.select_all(*q){|r| f.terminals << r}
      f.check_in_desks = []
      q = ["SELECT * FROM check_in_desks WHERE id = (SELECT check_in_desk_id FROM check_in_desk_flights WHERE flight_id = ?)", f[:id]]
      connection.select_all(*q){|r| f.check_in_desks << r}
      res << f
    end
    return res
  end
  
  def save(connection)
    query = ''
    params = []
    if self[:id].nil? 
      query = %(
      INSERT INTO #{self.table_name()}
            (#{(@attributes.keys - [:id]).join(', ')}) 
      VALUES(#{(@attributes.keys - [:id]).map{ |k| '?' }.join(', ')} ) RETURNING id
      )
      
      params = (@attributes.keys - [:id]).map{ |k| self[k] }
      
    else
      query = "UPDATE #{self.table_name()} SET " +
        (@attributes.keys - [:id]).map{ |k| "#{k} = ?" }.join(', ') +
        ' WHERE id = ? RETURNING id'
      params = (@attributes.keys - [:id]).map{ |k| self[k] } << self[:id]
    end
    rs = connection.select_one(query, *params)
    self[:id] = rs[0].to_i
  end

  def Flight.find_by_id(connection, id)
    id = id.to_i
    query = ["SELECT * FROM #{table_name()} WHERE id = ?", id]
    r = connection.select_one(*query)
    return nil if r.nil?
    f = self.new
    r.column_names.each do |c|
      f[c.to_sym] = r[c]
    end
    f.company = Company.find_by_id(connection,
      f[:company_id]) unless f[:company_id].nil?
    return f
  end
end
