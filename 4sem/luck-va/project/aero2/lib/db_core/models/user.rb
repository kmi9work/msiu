# To change this template, choose Tools | Templates
# and open the template in the editor.

class User < Model
  USER_COLUMNS = ['login', 'info']
  def User.create_table(connection)
    begin
      connection.do("
CREATE TABLE users(
  id serial PRIMARY KEY,
  login varchar(16) UNIQUE NOT NULL,
  password varchar(16) NOT NULL,
  info text,
  is_super boolean NOT NULL DEFAULT false
) WITH OIDS
        ")
      return true
    rescue DBI::ProgrammingError => e
      return false
    end
  end
  
  def save(connection)
    query = ''
    params = []
    begin
      if self[:id].nil? 
        query = "INSERT INTO users (" +
          (@attributes.keys - [:id]).join(', ') + ') VALUES (' +
          (@attributes.keys - [:id]).map{ |k| '?' }.join(', ') + ') RETURNING id'
        params = (@attributes.keys - [:id]).map{ |k| self[k] }
      
      else
        query = "UPDATE users SET " +
          (@attributes.keys - [:id]).map{ |k| "#{k} = ?" }.join(', ') +
          ' WHERE id = ? RETURNING id'
        params = (@attributes.keys - [:id]).map{ |k| self[k] } << self[:id]
      end
      rs = connection.select_one(query, *params)
      self[:id] = rs[0].to_i
      return true
    rescue
      return false
    end
  end
  
  def User.search(connection, str)
    queries = []
    str = str.to_s
    res = []
    queries << ['SELECT * FROM users WHERE login LIKE ?', str]
    queries << ['SELECT * FROM users WHERE info LIKE ?', str]
    queries.each_with_index do |query, index|
      connection.select_all(*query) do |r|
        f = self.new
        r.column_names.each do |column_name|
          f[column_name.to_sym] = r[column_name]
        end
        res << [f, index]
      end
    end
    return res
  end
  
  def User.find_by_login(connection, login)
    query = ['SELECT * FROM users WHERE login = ?', login]
    r = connection.select_one(*query)
    f = User.new
    r.column_names.each do |column_name|
      f[column_name.to_sym] = r[column_name]
    end
    return f
  end
  
  def to_s
    return "#{self[:is_super] ? 'Super user' : 'Easy user'} | #{self[:login]} | #{self[:info]}"
  end

  def User.check_user(connection, login, password)
    id = connection.select_one("SELECT id FROM users WHERE login = ? and password = ?", login, password)
    return (!id.nil?)
  end

  def User.create_admin(connection)
    connection.do("INSERT INTO users(login, password, info) VALUES('admin', 'qwerty', 'Администратор системы')")
  end
end

