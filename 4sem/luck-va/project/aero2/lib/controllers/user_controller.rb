class UserController < Controller
  def register
    if @user.nil?
      if @cgi.params.has_key?('is_commit')
        params = filter_for_params
        @item = User.new
        params.each do |k, v|
          @item[k] = v[0] if k != 'id' and v != '' and k != 'is_super' and k !~ /password[12]/
	  if k == 'is_super' 
	    if v[0] == '1'
	      @item[:is_super] = true
	    else
	      @item[:is_super] = false 
	    end	
	  end
        end
	if params['password1'] != params['password2']
	  @message = 'Пароли не совпадают'
	else
	  @item[:password] = params['password2'][0]
          if @item.save(@db)
            @message = 'Пользователь успешно создан'
          else
            @message = 'Невозможно создать пользователя'
          end
	end
        @link = "controller=User&action=show&id=#{@item[:id]}"
      else
        @header = 'Регистрация нового пользователя'
        @link = "controller=User&action=list"
      end
      render_template('register')
    else
      @message = 'Вы уже зарегистрированы'
      @link = 'controller=User&action=show'
      render_template('error')
    end
  end
  

  def is_authorized_action?
    false
  end    
  
  def search
    if @cgi.params.has_key?('is_commit')
      params = filter_for_params
      @items = User.search(@db, params['search']) if params['search'] != ''
    end
    render_template('search')
  end
  
  def edit
    if !@user.nil?
      if @cgi.params.has_key?('is_commit')
        params = filter_for_params
        if @user[:is_super]
          id = params['id'] unless params['id'] == ''
          id ||= @user[:id]
        else
          id = @user[:id]
        end
        @item = User.find_by_id(@db, id)
        params.each do |k, v|
          @item[k] = v[0] if k != 'id' and v != ''
        end
        if @item.save(@db)
          @message = 'Сделано.'
        else
          @message = 'Ошибка.'
        end
      else
        if @user[:is_super]
          id = @cgi.params['id'][0] unless @cgi.params['id'][0] == ''
          id ||= @user[:id]
        else
          id = @user[:id]
        end
        @header = 'Изменение информации о пользователе'
        @item = User.find_by_id(@db, id)
      end
      render_template('edit')
    else
      @message = 'У вас недостаточно прав'
      @link = 'controller=User&action=list'
      render_template('error')
    end
  end
  def destroy
    if !@user.nil?
      if @user[:is_super]
        id = @cgi.params['id'][0] or id = @user['id'] and @user = nil
      else
        if @cgi.params.has_key?('id')
          @message = 'У вас недостаточно прав'
          return render_template('destroy')
        end
        id = @user[:id] and @user = nil
      end
      @item = User.find_by_id(@db, id) if id
      unless @item.nil?
        @item.destroy(@db)
        @message = 'Удалено.'
      else
        @message = 'Объект не найден.'
      end
      render_template('destroy')
    else
      @message = 'У вас недостаточно прав'
      render_template('destroy')
    end
  end
  def show
    if (id = @cgi.params['id'][0] unless @cgi.params['id'][0] == '') or (id = @user['id'] if @user)
      @item = User.find_by_id(@db, id)
      render_template('show')
    else
      @message = 'Какая-то ошибка... Что-то Вы не так сделали... Я точно не виноват.'
      @link = 'controller=User&action=list'
      render_template('error')
    end
  end
  def list
    @items = User.find_all(@db)
    render_template('list')
  end  
end




