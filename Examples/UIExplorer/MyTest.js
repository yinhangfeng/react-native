'use strict';

var React = require('react');
var ReactNative = require('react-native');
var {
  StyleSheet,
  Text,
  View,
} = ReactNative;
var UIExplorerBlock = require('./UIExplorerBlock');
var UIExplorerButton = require('./UIExplorerButton');

class Test extends React.Component {

  shouldComponentUpdate() {
    console.log('Test shouldComponentUpdate');
    return true;
  }

  render() {
    console.log('Test render', this.props);
    return (
      <Text>test {this.props.id}</Text>
    );
  }
}

//如果重新渲染时 某个组件的element返回的就是上次的 则该组件不糊刷新 (shouldComponentUpdate render 都不会调用)
var MyTest = React.createClass({

  statics: {
    title: 'MyTest',
    description: 'MyTest',
  },

  render: function() {
    console.log('MyTest render');
    if(!this._test1) {
      this._test1 = <Test key={0} id={0}/>;
    }

    return (
      <UIExplorerBlock title="re render test">
        <UIExplorerButton
          onPress={() => {
            // this.setState({
            //   aaa: 1,
            // });
            this.forceUpdate();
          }}>
          test
        </UIExplorerButton>
        {this._test1}
      </UIExplorerBlock>
    );
  },
});

var styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: 'white',
    padding: 10,
    paddingTop: 30,
  },
  button: {
    padding: 10,
    backgroundColor: '#3B5998',
    marginBottom: 10,
  },
  text: {
    color: 'white',
  },
});

module.exports = MyTest;
