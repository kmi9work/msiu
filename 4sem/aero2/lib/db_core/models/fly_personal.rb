require 'db_core/models/model'

class FlyPersonal < Model
  JOBS = ['пилот', 'стюард', 'бортмеханик', 'второй пилот']

  def FlyPersonal.create_table(connection)
    begin
      connection.do("
CREATE TABLE fly_personals(
  id serial PRIMARY KEY,
  first_name text NOT NULL,
  second_name text NOT NULL,
  patronymic_name text,
  age integer NOT NULL, 
  job_title integer NOT NULL,
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
      :first_name => nil,
      :second_name => nil,
      :patronymic_name => nil,
      :age => nil, 
      :job_title => nil,
    }
    attributes.each do |k, v|
      @attributes[k.to_sym] = v unless v.nil? or v == ''
    end
  end

  def FlyPersonal.find_all_by_job_id(connection, id)
    id = id.to_i
    res = []
    query = ["SELECT * FROM fly_personals WHERE job_title = ?", id]
    connection.select_all(*query) do |r|
      f = self.new
      r.column_names.each do |c|
        f[c.to_sym] = r[c]
      end
      res << f
    end
    return res
  end
end
