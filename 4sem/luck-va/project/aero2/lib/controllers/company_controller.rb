class CompanyController < Controller
  def list
    @items = Company.find_all(@db)
    @header = 'Авиакомпании'
    render_template('list')
  end
  
  def show
    if @cgi.params.has_key?('company_id') and @cgi.params['company_id'][0] != ''
      @item = Company.find_by_id(@db, @cgi.params['company_id'][0])
      render_template('show')
    else
      @message = 'Нет такой компании.'
      render_template('error')
    end
  end
  
  def edit
    if @user and !@user[:is_super]
      if @cgi.params.has_key?('is_commit')
        params = filter_for_params()
        if params.has_key?('id') and params['id'][0] != ''
          @item = Company.find_by_id(@db, params['id'][0])
          if @item.nil?
            @item = Company.new
            @header = 'Добавление авиакомпании1'
            @message = 'Авиакомпания записана1'
          else
            @item = Company.find_by_id(@db, params['id'][0])
            @header = 'Редактирование авиакомпании'
            @message = 'Информация о авиакомпании изменена'
          end
        else
          @item = Company.new
          @header = 'Добавление авиакомпании'
          @message = 'Авиакомпания записана'
        end
        params.each do |k, v|
          @item[k] = v[0] if k != 'id' and v != ''
        end
        @item.save(@db)
      else
        if @cgi.params.has_key?('id')
          @item = Company.find_by_id(@db, @cgi.params['id'][0])
          if @item.nil?
            @item = Company.new
            @header = 'Добавление авиакомпании'
          else
            @header = 'Редактирование авиакомпании'
          end
        else
          @item = Company.new
          @header = 'Внесение новой информации о авиакомпании'
        end
      end
      render_template('edit')
    else
      @message = 'Недостаточно прав'
      @link = 'controller=Company&action=list'
      render_template('error')
    end
  end
  def destroy()
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Company.find_by_id(@db, @cgi.params['id'][0])
      unless @item.nil?
        @item.destroy(@db)
        @message = 'Объект удален!'
      else
        @message = 'Объект не найден!'
      end
    end
    render_template(@action)
  end
end
