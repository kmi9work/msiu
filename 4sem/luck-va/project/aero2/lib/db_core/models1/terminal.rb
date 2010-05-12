require 'db_core/models/model'

class Terminal < Model
  def Terminal.create_table(connection)
    begin
      connection.do("
CREATE TABLE terminals(
  id serial PRIMARY KEY,
  name varchar(8) UNIQUE NOT NULL,
  description text,
  needs_bus boolean NOT NULL DEFAULT false
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end
  def Terminal.find_all(connection)
    query = []
    res = []
    query = ["SELECT * FROM terminals 
      ORDER BY code, name"]
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
